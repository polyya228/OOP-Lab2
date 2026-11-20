#pragma once
#include "Unit.h"
#include "TerrainProxy.h"
#include "NeutralObject.h"
#include "Observer.h"          
#include <vector>
#include <memory>

class TerrainMap : public IObserver, public std::enable_shared_from_this<TerrainMap> {
private:
    int width;
    int height;
    std::vector<std::vector<std::unique_ptr<TerrainProxy>>> terrainGrid;
    std::vector<std::shared_ptr<Unit>> units;
    std::vector<std::vector<std::shared_ptr<NeutralObject>>> neutralObjects;

public:
    TerrainMap(int w, int h);
    Terrain* getTerrain(int x, int y) const;
    void addUnit(std::shared_ptr<Unit> unit, int x, int y);
    Unit* getUnit(int x, int y) const;
    NeutralObject* getNeutralObjectAt(int x, int y);
    void addNeutralObject(std::shared_ptr<NeutralObject> obj, int x, int y);
    void onUnitEvent(const UnitEvent& event) override;
    void subscribeToUnit(const std::shared_ptr<Unit>& unit);
    void setTerrain(int x, int y, std::unique_ptr<Terrain> terrain);

    int getWidth() const;
    int getHeight() const;

    auto begin() { return units.begin(); }
    auto end() { return units.end(); }
    auto begin() const { return units.begin(); }
    auto end() const { return units.end(); }
};
