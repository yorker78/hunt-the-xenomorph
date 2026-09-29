#include "item.h"

using namespace std;

void Flamethrower::use() {
    fuel--;
}

bool Flamethrower::usable() {
    return fuel > 0;
}

void LoaderSuit::use() {
    canBeUsed = false;
}

bool LoaderSuit::usable() {
    return canBeUsed;
}

void Tracker::use() {
    canBeUsed = false;
}

bool Tracker::usable() {
    return canBeUsed;
}

void CoolantTrap::use() {
    canBeUsed = false;
}

bool CoolantTrap::usable() {
    return canBeUsed;
}