#include "Unit.h"
#include <algorithm>

using namespace std;

Unit::Unit(int id, std::shared_ptr<UnitTypeInfo> info, int startX, int startY)
    : id(id), info(info), currentHealth(info->maxHealth),
    currentAttack(info->baseAttack), currentMana(0), x(startX), y(startY) {}

void Unit::setPosition(int newX, int newY) { x = newX; y = newY; }
int Unit::getX() const { return x; }
int Unit::getY() const { return y; }
int Unit::getHealthValue() const { return currentHealth; }
int Unit::getId() const { return id; }
int Unit::getAttackValue() const { return currentAttack; }
int Unit::getManaValue() const { return currentMana; }
UnitType Unit::getType() const { return info->type; }
int Unit::getMaxHealth() const { return info->maxHealth; }

void Unit::subscribe(const std::shared_ptr<IObserver>& observer) {
    if (!observer) return;

    for (const auto& weak : observers_) {
        if (weak.lock() == observer) return;
    }
    observers_.push_back(observer);
}

void Unit::unsubscribe(const std::shared_ptr<IObserver>& observer) {
    observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
        [&](const std::weak_ptr<IObserver>& weak) {
            return weak.expired() || weak.lock() == observer;
        }), observers_.end());
}
void Unit::notify(const UnitEvent& event) {
    const auto snapshot = observers_;
    for (const auto& weak : snapshot) {
        if (auto observer = weak.lock()) {
            observer->onUnitEvent(event);
        }
    }
}

void Unit::heal(int amount) {
    currentHealth += amount;
    if (currentHealth > info->maxHealth) currentHealth = info->maxHealth;
}

void Unit::boostAttack(int amount) {
    currentAttack += amount;
    cout << "(Unit) Атака увеличена на " << amount << ". Новая сила атаки: " << currentAttack << endl;
}

void Unit::boostMana(int amount) {
    currentMana += amount;
    cout << "(Unit) Мана увеличена на " << amount << ". Новое значение маны: " << currentMana << endl;
}

void Unit::takeDamage(int amount) {
    currentHealth -= amount;
    notify({ UnitEventType::Damaged, id, amount, std::chrono::system_clock::now() });
    if (currentHealth <= 0) {
        notify({ UnitEventType::Destroyed, id, 0, std::chrono::system_clock::now() });
    }
}