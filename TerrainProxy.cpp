#include "TerrainProxy.h"
#include <iostream>

using namespace std;

bool TerrainProxy::isPassable(const Unit& unit) const {
    cout << "(Proxy) Проверка проходимости для юнита " << unit.getId()
        << " (Тип: " << static_cast<int>(unit.getType()) << ")" << endl;

    if (unit.getType() == UnitType::Flying) {
        cout << "(Proxy) Юнит умеет летать, проверка рельефа пропущена." << endl;
        return true;
    }

    bool result = realTerrain->isPassable(unit);
    cout << "(Proxy) Результат: " << (result ? "проходимо" : "заблокированно") << endl;
    return result;
}

double TerrainProxy::getSpeedModifier(const Unit& unit) const {
    if (unit.getType() == UnitType::Flying) {
        cout << "(Proxy) Юнит летит, модификатор скорости = 1.0" << endl;
        return 1.0;
    }
    double modifier = realTerrain->getSpeedModifier(unit);
    cout << "(Proxy) Модификатор скорости для юнита " << unit.getId() << ": " << modifier << endl;
    return modifier;
}

double TerrainProxy::getDefenseBonus(const Unit& unit) const {
    if (unit.getType() == UnitType::Flying) {
        cout << "(Proxy) Юнит летит, бонус к защите = 0.0" << endl;
        return 0.0;
    }
    double bonus = realTerrain->getDefenseBonus(unit);
    cout << "(Proxy) Бонус к защите для юнита " << unit.getId() << ": " << bonus << endl;
    return bonus;
}