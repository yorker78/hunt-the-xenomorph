#include "room.h"

using namespace std;

void EmptyRoom::print() {
    cout << "-";
}

void ProtoNest::print() {
    cout << "N";
}

void Airlock::print() {
    cout << "A";
}

void ShuttleBay::print() {
    cout << "S";
}

void MedBay::print() {
    cout << "M";
}

void CargoBay::print() {
    cout << "C";
}

bool Airlock::getCanBeOpened() {
    return canBeOpened;
}

void Airlock::setCanBeOpened(bool canOpen) {
    canBeOpened = canOpen;
}