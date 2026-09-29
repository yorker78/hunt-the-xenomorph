#ifndef CHARACTER_H
#define CHARACTER_H

#include "room.h"
#include <set>

class Character {
    private:
        Room* currentRoom;
    public:
        Character(Room* startingRoom) : currentRoom(startingRoom) {};
        void move(Room* room) {currentRoom = room;};
        Room* getRoom() {return currentRoom;}
};

class Ripley : public Character {
    private:
        std::list<Item*> items;
    public:
        Ripley(Room* startingRoom) : Character(startingRoom) {};
        std::list<Item*> getItems() {return items;}
        void addItem(Item* newItem) {items.push_back(newItem);}
};

class Alien : public Character {
    private:
        Room* trackedRoom;
        std::list<Room*> pathToTrackedRoom;
        bool awake;
        bool checkVisitedRoom(Room* room, std::set<Room*> visited);
    public:
        Alien(Room* startingRoom) : Character(startingRoom), awake(false) {};
        void setTrackedRoom(Room* room) {trackedRoom = room;};
        Room* getTrackedRoom() {return trackedRoom;};
        std::list<Room*> getPathToTrackedRoom();
        bool isAwake() {return awake;}
        void setAwake(bool wakeStatus) {awake = wakeStatus;}
};
#endif