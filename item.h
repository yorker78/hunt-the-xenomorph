//
// Created by Ryan Malvey on 4/11/2024.
//

#ifndef HUNT_THE_XENOMORPH_ITEM_H
#define HUNT_THE_XENOMORPH_ITEM_H

#include <iostream>

class Item {
    public:
        Item() {};
        virtual ~Item() {};
        virtual void use() = 0;
        virtual bool usable() = 0;
};

class Flamethrower : public Item {
    private:
        int fuel;
    public:
        Flamethrower() : Item(), fuel(3) {};
        void use();
        bool usable();
};

class LoaderSuit : public Item {
    private:
        bool canBeUsed;
    public:
        LoaderSuit() : Item(), canBeUsed(true) {};
        void use();
        bool usable();
};

class Tracker : public Item {
    private:
        bool canBeUsed;
    public:
        Tracker() : Item(), canBeUsed(true) {};
        void use();
        bool usable();
};

class CoolantTrap : public Item {
    private:
        bool canBeUsed;
    public:
        CoolantTrap() : Item(), canBeUsed(true) {};
        void use();
        bool usable();
};

#endif //HUNT_THE_XENOMORPH_ITEM_H
