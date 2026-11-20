#pragma once
#include "Unit.h"
#include <memory>
#include <iostream>

using namespace std;

class Base;

//методы принимают Unit& (не const), потому что
//стратегии меняют юнита (лечат, наносят урон, увеличивают атаку).
class InteractionStrategy {
public:
    virtual void apply(Unit& unit) = 0;
    virtual ~InteractionStrategy() = default;
};

class AttackBoostStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) override {
        cout << "(Strategy) Увеличение атаки для юнита " << unit.getId() << endl;
        unit.boostAttack(10);
    }
};

class HealthRestoreStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) override {
        cout << "(Strategy) Восстановление здоровья для юнита " << unit.getId() << endl;
        unit.heal(50);
    }
};

class ManaBoostStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) override {
        cout << "(Strategy) Увеличение маны для юнита " << unit.getId() << endl;
        unit.boostMana(20);
    }
};

class DamageStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) override {
        cout << "(Strategy) Получение урона юнитом " << unit.getId() << endl;
        unit.takeDamage(20);
    }
};

class ResourceStrategy : public InteractionStrategy {
private:
    Base* base;
public:
    ResourceStrategy(Base* b) : base(b) {}
    void apply(Unit& unit) override;
};

class FullHealStrategy : public InteractionStrategy {
public:
    void apply(Unit& unit) override {
        cout << "(Strategy) Полное восстановление здоровья для юнита " << unit.getId() << endl;
        unit.heal(unit.getMaxHealth());  
    }
};


class NeutralObject {
protected:
    std::shared_ptr<InteractionStrategy> strategy;
public:
    NeutralObject(std::shared_ptr<InteractionStrategy> s) : strategy(std::move(s)) {}
    virtual void interact(Unit& unit) = 0;
    virtual ~NeutralObject() = default;
};

class TreasureChest : public NeutralObject {
public:
    TreasureChest(Base* base) : NeutralObject(std::make_shared<ResourceStrategy>(base)) {}
    void interact(Unit& unit) override { strategy->apply(unit); }
};

class Trap : public NeutralObject {
public:
    Trap() : NeutralObject(std::make_shared<DamageStrategy>()) {}
    void interact(Unit& unit) override { strategy->apply(unit); }
};

class Altar : public NeutralObject {
public:
    Altar() : NeutralObject(nullptr) {}
    void interact(Unit& unit) override {
        switch (unit.getType()) {
        case UnitType::Infantry:
            strategy = std::make_shared<AttackBoostStrategy>();
            break;
        case UnitType::Archer:
            strategy = std::make_shared<ManaBoostStrategy>();
            break;
        case UnitType::Mage:
            strategy = std::make_shared<ManaBoostStrategy>();
            break;
        case UnitType::Flying:
            strategy = std::make_shared<HealthRestoreStrategy>();
            break;
        default:
            cout << "(Altar) Неизвестный тип юнита, взаимодействие отменено." << endl;
            strategy = nullptr;
            break;
        }

        if (strategy) { strategy->apply(unit); }
        else { cout << "(Altar) Стратегия не выбрана, взаимодействие не выполнено." << endl; }
    }
};

class EnergySource : public NeutralObject {
public:
    EnergySource() : NeutralObject(std::make_shared<FullHealStrategy>()) {}
    void interact(Unit& unit) override { strategy->apply(unit); }
};

inline Unit& operator+(Unit& unit, TreasureChest& chest) {
    chest.interact(unit);
    return unit;
}

inline Unit& operator-(Unit& unit, Trap& trap) {
    trap.interact(unit);
    return unit;
}

inline Unit& operator*(Unit& unit, Altar& altar) {
    altar.interact(unit);
    return unit;
}

inline Unit& operator/(Unit& unit, EnergySource& source) {
    source.interact(unit);
    return unit;
}