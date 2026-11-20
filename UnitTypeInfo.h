#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <mutex> 

enum class UnitType {
    Infantry,
    Archer,
    Mage,
    Flying
};

class UnitTypeInfo {
public:
    const int maxHealth;
    const int baseAttack;
    const int baseSpeed;
    const int cost;
    const UnitType type;

    UnitTypeInfo(int hp, int atk, int spd, int cst, UnitType t);

    static std::shared_ptr<UnitTypeInfo> getInfo(UnitType type);

private:
    static std::unordered_map<UnitType, std::shared_ptr<UnitTypeInfo>> pool;
    static std::once_flag poolFlag; 
    static void initPool();
};