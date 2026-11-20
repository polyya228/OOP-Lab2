#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>

enum class UnitEventType {
    Created,
    Damaged,
    Destroyed
};

struct UnitEvent {
    UnitEventType type;
    int unitId;
    int damage;
    std::chrono::system_clock::time_point timestamp;
};

class IObserver {
public:
    virtual void onUnitEvent(const UnitEvent& event) = 0;
    virtual ~IObserver() = default;
};

class IObservable {
public:
    virtual void subscribe(const std::shared_ptr<IObserver>& observer) = 0;
    virtual void unsubscribe(const std::shared_ptr<IObserver>& observer) = 0;
    virtual void notify(const UnitEvent& event) = 0;
    virtual ~IObservable() = default;
};