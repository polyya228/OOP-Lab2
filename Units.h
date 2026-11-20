#pragma once
#include "Unit.h"

class Infantry : public Unit {
public:
    Infantry(int id, std::shared_ptr<UnitTypeInfo> info, int startX, int startY)
        : Unit(id, info, startX, startY) {
    }
};

class Archer : public Unit {
public:
    Archer(int id, std::shared_ptr<UnitTypeInfo> info, int startX, int startY)
        : Unit(id, info, startX, startY) {
    }
};

class Mage : public Unit {
public:
    Mage(int id, std::shared_ptr<UnitTypeInfo> info, int startX, int startY)
        : Unit(id, info, startX, startY) {
    }
};

class FlyingUnit : public Unit {
public:
    FlyingUnit(int id, std::shared_ptr<UnitTypeInfo> info, int startX, int startY)
        : Unit(id, info, startX, startY) {
    }
};

class DwarfGuard : public Infantry {
public:
    DwarfGuard(int id, int x, int y)
        : Infantry(id, UnitTypeInfo::getInfo(UnitType::Infantry), x, y) {
    }
    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<DwarfGuard>(id, getX(), getY());
    }
    void move(int newX, int newY) override { setPosition(newX, newY); }
    void attack(Unit& target) override;
};

class ElfRanger : public Archer {
public:
    ElfRanger(int id, int x, int y)
        : Archer(id, UnitTypeInfo::getInfo(UnitType::Archer), x, y) {
    }
    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<ElfRanger>(id, getX(), getY());
    }
    void move(int newX, int newY) override { setPosition(newX, newY); }
    void attack(Unit& target) override;
};

class ElfHealer : public Mage {
public:
    ElfHealer(int id, int x, int y)
        : Mage(id, UnitTypeInfo::getInfo(UnitType::Mage), x, y) {
    }
    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<ElfHealer>(id, getX(), getY());
    }
    void move(int newX, int newY) override { setPosition(newX, newY); }
    void attack(Unit& target) override;
};

class OrcBerserker : public Infantry {
public:
    OrcBerserker(int id, int x, int y)
        : Infantry(id, UnitTypeInfo::getInfo(UnitType::Infantry), x, y) {
    }
    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<OrcBerserker>(id, getX(), getY());
    }
    void move(int newX, int newY) override { setPosition(newX, newY); }
    void attack(Unit& target) override;
};

class GoblinGunner : public Archer {
public:
    GoblinGunner(int id, int x, int y)
        : Archer(id, UnitTypeInfo::getInfo(UnitType::Archer), x, y) {
    }
    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<GoblinGunner>(id, getX(), getY());
    }
    void move(int newX, int newY) override { setPosition(newX, newY); }
    void attack(Unit& target) override;
};

class DarkWarlock : public Mage {
public:
    DarkWarlock(int id, int x, int y)
        : Mage(id, UnitTypeInfo::getInfo(UnitType::Mage), x, y) {
    }
    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<DarkWarlock>(id, getX(), getY());
    }
    void move(int newX, int newY) override { setPosition(newX, newY); }
    void attack(Unit& target) override;
};

class Griffin : public FlyingUnit {
public:
    Griffin(int id, int x, int y)
        : FlyingUnit(id, UnitTypeInfo::getInfo(UnitType::Flying), x, y) {
    }
    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<Griffin>(id, getX(), getY());
    }
    void move(int newX, int newY) override { setPosition(newX, newY); }
    void attack(Unit& target) override;
};

class Gargoyle : public FlyingUnit {
public:
    Gargoyle(int id, int x, int y)
        : FlyingUnit(id, UnitTypeInfo::getInfo(UnitType::Flying), x, y) {
    }
    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<Gargoyle>(id, getX(), getY());
    }
    void move(int newX, int newY) override { setPosition(newX, newY); }
    void attack(Unit& target) override;
};