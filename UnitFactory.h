#pragma once
#include "Units.h"
#include <memory>

class UnitFactory {
public:
    virtual std::unique_ptr<Unit> createInfantry(int x, int y) const = 0;
    virtual std::unique_ptr<Unit> createArcher(int x, int y) const = 0;
    virtual std::unique_ptr<Unit> createMage(int x, int y) const = 0;
    virtual std::unique_ptr<Unit> createFlying(int x, int y) const = 0;
    virtual ~UnitFactory() = default;
};

class ForestFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createInfantry(int x, int y) const override {
        return std::make_unique<DwarfGuard>(1, x, y);
    }
    std::unique_ptr<Unit> createArcher(int x, int y) const override {
        return std::make_unique<ElfRanger>(2, x, y);
    }
    std::unique_ptr<Unit> createMage(int x, int y) const override {
        return std::make_unique<ElfHealer>(3, x, y);
    }
    std::unique_ptr<Unit> createFlying(int x, int y) const override {
        return std::make_unique<Griffin>(4, x, y); 
    }
};

class UmbralFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createInfantry(int x, int y) const override {
        return std::make_unique<OrcBerserker>(5, x, y);
    }
    std::unique_ptr<Unit> createArcher(int x, int y) const override {
        return std::make_unique<GoblinGunner>(6, x, y);
    }
    std::unique_ptr<Unit> createMage(int x, int y) const override {
        return std::make_unique<DarkWarlock>(7, x, y);
    }
    std::unique_ptr<Unit> createFlying(int x, int y) const override {
        return std::make_unique<Gargoyle>(8, x, y); 
    }
};