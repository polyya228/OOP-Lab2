#include "UnitTypeInfo.h"
#include <mutex> 

std::unordered_map<UnitType, std::shared_ptr<UnitTypeInfo>> UnitTypeInfo::pool;
std::once_flag UnitTypeInfo::poolFlag;  

UnitTypeInfo::UnitTypeInfo(int hp, int atk, int spd, int cst, UnitType t)
    : maxHealth(hp), baseAttack(atk), baseSpeed(spd), cost(cst), type(t) {
}

void UnitTypeInfo::initPool() {
    std::call_once(poolFlag, []() {
        pool[UnitType::Infantry] = std::make_shared<UnitTypeInfo>(200, 15, 1, 50, UnitType::Infantry);
        pool[UnitType::Archer] = std::make_shared<UnitTypeInfo>(80, 35, 2, 40, UnitType::Archer);
        pool[UnitType::Mage] = std::make_shared<UnitTypeInfo>(60, 10, 1, 60, UnitType::Mage);
        pool[UnitType::Flying] = std::make_shared<UnitTypeInfo>(90, 20, 3, 70, UnitType::Flying);
        });
}

std::shared_ptr<UnitTypeInfo> UnitTypeInfo::getInfo(UnitType type) {
    initPool();
    return pool[type];
}