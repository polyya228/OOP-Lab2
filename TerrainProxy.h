#pragma once
#include "Terrain.h"
#include <memory>

class TerrainProxy : public Terrain {
private:
    std::unique_ptr<Terrain> realTerrain;
public:
    TerrainProxy(std::unique_ptr<Terrain> t) : realTerrain(std::move(t)) {}
    bool isPassable(const Unit& unit) const override;
    double getSpeedModifier(const Unit& unit) const override;
    double getDefenseBonus(const Unit& unit) const override;
};