#pragma once
#include "Unit.h"
#include "Observer.h"
#include "UnitFactory.h"
#include <vector>
#include <memory>

class Base : public IObserver, public std::enable_shared_from_this<Base> {
private:
    int health;
    int maxUnits;
    int defenseLevel;
    int resources;
    int x;
    int y;
    std::vector<std::shared_ptr<Unit>> units;
    std::vector<int> destroyedUnits;
    UnitFactory* factory;

public:
    Base(int hp, int maxU, int def, int res, UnitFactory* f, int startX = 0, int startY = 0);
    std::shared_ptr<Unit> createUnit(UnitType type, int x, int y);
    void removeUnit(int unitId);
    void onUnitEvent(const UnitEvent& event) override;
    void addResources(int amount) { resources += amount; }

    int getHealth() const;
    int getMaxUnits() const;
    int getDefenseLevel() const;
    int getResources() const;
    int getUnitCount() const;
    int getX() const; 
    int getY() const;
    const std::vector<int>& getDestroyedUnits() const;

    auto begin() { return units.begin(); }
    auto end() { return units.end(); }
    auto begin() const { return units.begin(); }
    auto end() const { return units.end(); }
};
