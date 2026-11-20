#include "Units.h"

static void dealDamage(Unit& attacker, Unit& target) {
    int damage = attacker.getAttackValue(); 
    target.takeDamage(damage);
}

void DwarfGuard::attack(Unit& target) { dealDamage(*this, target); }

void ElfRanger::attack(Unit& target) { dealDamage(*this, target); }

void ElfHealer::attack(Unit& target) { dealDamage(*this, target); }

void OrcBerserker::attack(Unit& target) { dealDamage(*this, target); }

void GoblinGunner::attack(Unit& target) { dealDamage(*this, target); }

void DarkWarlock::attack(Unit& target) { dealDamage(*this, target); }

void Griffin::attack(Unit& target) { dealDamage(*this, target); }

void Gargoyle::attack(Unit& target) { dealDamage(*this, target); }