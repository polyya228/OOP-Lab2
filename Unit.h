#pragma once
#include <memory>
#include <vector>
#include "UnitTypeInfo.h"
#include "Observer.h"

class Unit : public IObservable {
protected:
    int id;
    int currentHealth;
    int currentAttack;
    int currentMana;
    int x;
    int y;
    std::shared_ptr<UnitTypeInfo> info;
    std::vector<std::weak_ptr<IObserver>> observers_;

public:
    Unit(int id, std::shared_ptr<UnitTypeInfo> info, int startX, int startY);
    virtual ~Unit() = default;

    void setPosition(int newX, int newY);
    int getX() const;
    int getY() const;
    int getHealthValue() const;
    int getId() const;
    UnitType getType() const;
    int getAttackValue() const;
    int getManaValue() const;
    int getMaxHealth() const;

    void subscribe(const std::shared_ptr<IObserver>& observer) override;
    void unsubscribe(const std::shared_ptr<IObserver>& observer) override;
    void notify(const UnitEvent& event) override;

    virtual void move(int newX, int newY) = 0;
    virtual void attack(Unit& target) = 0;
    virtual void takeDamage(int amount);
    void heal(int amount);
    void boostAttack(int amount);
    void boostMana(int amount);

    virtual std::unique_ptr<Unit> clone() const = 0;
};