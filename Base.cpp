#include "Base.h"
#include <iostream>
#include <algorithm>

using namespace std;

Base::Base(int hp, int maxU, int def, int res, UnitFactory* f, int startX, int startY)
    : health(hp), maxUnits(maxU), defenseLevel(def), resources(res),
    x(startX), y(startY), factory(f) {}

std::shared_ptr<Unit> Base::createUnit(UnitType type, int x, int y) {
    if ((int)units.size() >= maxUnits) {
        cout << "(Base) Невозможно создать юнита: достигнут максимальный лимит." << endl;
        return nullptr;
    }
    if (factory == nullptr) {
        cout << "(Base) Не удаётся создать юнита: не назначена фабрика." << endl;
        return nullptr;
    }

    std::unique_ptr<Unit> newUnit = nullptr;
    switch (type) {
    case UnitType::Infantry: 
        newUnit = factory->createInfantry(x, y); 
        break;
    case UnitType::Archer:   
        newUnit = factory->createArcher(x, y);   
        break;
    case UnitType::Mage:     
        newUnit = factory->createMage(x, y);     
        break;
    case UnitType::Flying:
        newUnit = factory->createFlying(x, y);
        break;
    default:
        cout << "(Base) Неизвестный тип юнита." << endl;
        break;
    }

    if (newUnit != nullptr) {
        std::shared_ptr<Unit> unitPtr = std::move(newUnit);
        units.push_back(unitPtr);
        unitPtr->subscribe(shared_from_this());
        unitPtr->notify({ UnitEventType::Created, unitPtr->getId(), 0, std::chrono::system_clock::now() });
        return unitPtr; 
    }
    return nullptr;
}

void Base::removeUnit(int unitId) {
    units.erase(std::remove_if(units.begin(), units.end(),
        [unitId](const std::shared_ptr<Unit>& u) { return u->getId() == unitId; }), units.end()); 
}

void Base::onUnitEvent(const UnitEvent& event) {
    if (event.type == UnitEventType::Destroyed) {
        removeUnit(event.unitId);
        destroyedUnits.push_back(event.unitId);
        cout << "(Base) Юнит " << event.unitId << " уничтожен. Удаление с базы." << endl;
    }
    else if (event.type == UnitEventType::Damaged) {
        cout << "(Base) Юнит " << event.unitId << " получил " << event.damage << " урона." << endl;
    }
    else if (event.type == UnitEventType::Created) {
        cout << "(Base) Юнит " << event.unitId << " создан." << endl;
    }
}

int Base::getHealth() const { return health; }
int Base::getMaxUnits() const { return maxUnits; }
int Base::getDefenseLevel() const { return defenseLevel; }
int Base::getResources() const { return resources; }
int Base::getUnitCount() const { return (int)units.size(); }
int Base::getX() const { return x; }
int Base::getY() const { return y; }
const std::vector<int>& Base::getDestroyedUnits() const { return destroyedUnits; }