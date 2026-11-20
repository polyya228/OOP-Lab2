#pragma once
#include "Unit.h"

//методы принимают const Unit&, потому что ландшафт
//только читает юнита, но не меняет его. const защищает от
//случайного изменения и избегает лишних копий.
class Terrain {
public:
    virtual ~Terrain() = default;
    virtual bool isPassable(const Unit& unit) const = 0;
    virtual double getSpeedModifier(const Unit& unit) const = 0;
    virtual double getDefenseBonus(const Unit& unit) const = 0;
};

class Plains : public Terrain {
public:
    bool isPassable(const Unit& unit) const override { return true; }
    double getSpeedModifier(const Unit& unit) const override { return 1.0; }
    double getDefenseBonus(const Unit& unit) const override { return 0.0; }
};

class Forest : public Terrain {
public:
    bool isPassable(const Unit& unit) const override { return true; }
    double getSpeedModifier(const Unit& unit) const override { return 0.5; }
    double getDefenseBonus(const Unit& unit) const override { return 0.2; }
};

class Swamp : public Terrain {
public:
    bool isPassable(const Unit& unit) const override { return true; }
    double getSpeedModifier(const Unit& unit) const override { return 0.25; }
    double getDefenseBonus(const Unit& unit) const override { return 0.0; }
};

class Mountains : public Terrain {
public:
    bool isPassable(const Unit& unit) const override { return unit.getType() == UnitType::Flying; }
    double getSpeedModifier(const Unit& unit) const override { return 1.0; }
    double getDefenseBonus(const Unit& unit) const override { return 0.0; }
};