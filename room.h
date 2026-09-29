//Room.h
#ifndef ROOM_H
#define ROOM_H

#include "item.h"
#include <list>
#include <cmath>

class Room {
private:
    Room* north;
    Room* south;
    Room* east;
    Room* west;
    Room* vent;
    Item* item;
    bool trapped;
protected:
    int x;
    int y;

public:
    //Constructor
    Room() : north(nullptr), south(nullptr), east(nullptr), west(nullptr), vent(nullptr), item(nullptr), trapped(false) {}

    //Destructor (currently virtual because I don't know exactly what we will be doing with it yet)
    virtual ~Room() {}

    //Print function
    virtual void print() = 0;

    //Setters for room pointers
    void setNorth(Room* room) { north = room; }
    void setSouth(Room* room) { south = room; }
    void setEast(Room* room) { east = room; }
    void setWest(Room* room) { west = room; }
    void setVent(Room* room) { vent = room; }

    //Getters for room pointers
    Room* getNorth() const { return north; }
    Room* getSouth() const { return south; }
    Room* getEast() const { return east; }
    Room* getWest() const { return west; }
    Room* getVent() const { return vent; }

    void setItem(Item* newItem) {item = newItem;}
    Item* getItem() {return item;}

    int getX() const { return x; }
    int getY() const { return y; }

    bool trappedStatus() const { return trapped; }
    void setTrap(bool trap) { trapped = trap; }
};

class EmptyRoom : public Room {
    public:
        EmptyRoom() : Room() {};
        void print();
};

class ProtoNest : public Room {
    public:
        ProtoNest() : Room() {
            this->x = (rand() % 3) + 1;
            this->y = (rand() % 3) + 1;
        };
        void print();
};

class Airlock : public Room {
    private:
    bool canBeOpened;
    public:
        Airlock() : Room(), canBeOpened(true) {
            if(rand() % 2 == 0) {
                this->x = (rand() % 2) * 4;
                this->y = rand() % 5;
            } else {
                this->x = rand() % 5;
                this->y = (rand() % 2) * 4;
            }
        };
        void print();
        bool getCanBeOpened();
        void setCanBeOpened(bool canOpen);
};

class ShuttleBay : public Room {
    public:
        ShuttleBay(Room* al) : Room() {
            this->x = rand() % 5;
            if(al->getY() == 0 || al->getY() == 4)
                this->y = (al->getY() == 0) * 4;
            else
                this->y = (rand() % 2) * 4;
        };
        void print();
};

class MedBay : public Room {
    public:
        MedBay(Room* pn) : Room() {
            int xSteps = rand() % (2 + (pn->getX() % 2));
            int xSign = pow(-1, (pn->getX() / 2));
            int ySteps = (rand() % (xSteps + 1)) + (2 - xSteps);
            int ySign = pow(-1, (pn->getY() / 2));
            if(pn->getX() == 2) {
                xSign = pow(-1, rand() % 2);
            }
            if(pn->getY() == 2) {
                ySign = pow(-1, rand() % 2);
                ySteps = rand() % 2;
                xSteps = (rand() % (ySteps + 1)) + (2 - ySteps);
            }
            if(pn->getX() == 2 && pn->getY() == 2) {
                xSteps = 1;
                ySteps = 1;
            }
            this->x = (xSteps * xSign) + pn->getX();
            this->y = (ySteps * ySign) + pn->getY();
        };
        void print();
};

class CargoBay : public Room {
    public:
        CargoBay(Room* al, Room* sb) : Room() {
            std::list<int> pos;
            pos.push_back(0);
            pos.push_back(1);
            pos.push_back(2);
            pos.push_back(3);
            pos.push_back(4);
            if(al->getX() == 4)
                pos.remove(al->getY());
            if(sb->getX() == 4)
                pos.remove(sb->getY());
            int i = rand() % pos.size();
            std::list<int>::iterator it = pos.begin();
            advance(it, i);
            this->x = 4;
            this->y = *it;
        };
        void print();
};
#endif