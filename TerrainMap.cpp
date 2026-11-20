#include "TerrainMap.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

TerrainMap::TerrainMap(int w, int h) : width(w), height(h) {
    terrainGrid.resize(height);
    neutralObjects.resize(height);
    for (int y = 0; y < height; ++y) {
        terrainGrid[y].resize(width);
        neutralObjects[y].resize(width);
        for (int x = 0; x < width; ++x) {
            terrainGrid[y][x] = std::make_unique<TerrainProxy>(std::make_unique<Plains>());
            neutralObjects[y][x] = nullptr;
        }
    }
}

Terrain* TerrainMap::getTerrain(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return nullptr;
    return terrainGrid[y][x].get();
}

void TerrainMap::addUnit(std::shared_ptr<Unit> unit, int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        throw std::out_of_range("Координаты за пределами поля.");
    unit->setPosition(x, y);
    units.push_back(unit);
    subscribeToUnit(unit);
}

Unit* TerrainMap::getUnit(int x, int y) const {
    for (const auto& u : units) {
        if (u->getX() == x && u->getY() == y) return u.get();
    }
    return nullptr;
}

void TerrainMap::addNeutralObject(std::shared_ptr<NeutralObject> obj, int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        throw std::out_of_range("Координаты за пределами поля.");
    neutralObjects[y][x] = obj;
}

void TerrainMap::subscribeToUnit(const std::shared_ptr<Unit>& unit) {
    if (unit) {
        unit->subscribe(shared_from_this());
    }
}

void TerrainMap::onUnitEvent(const UnitEvent& event) {
    if (event.type == UnitEventType::Destroyed) {
        units.erase(std::remove_if(units.begin(), units.end(),
            [&event](const std::shared_ptr<Unit>& u) {
                return u->getId() == event.unitId;
            }), units.end());
        std::cout << "(Map) Юнит " << event.unitId << " удалён с карты." << std::endl;
    }
}

NeutralObject* TerrainMap::getNeutralObjectAt(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) return nullptr;
    return neutralObjects[y][x].get();
}

void TerrainMap::setTerrain(int x, int y, std::unique_ptr<Terrain> terrain) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        throw std::out_of_range("Координаты за пределами поля.");
    terrainGrid[y][x] = std::make_unique<TerrainProxy>(std::move(terrain));
}

int TerrainMap::getWidth() const { return width; }
int TerrainMap::getHeight() const { return height; }