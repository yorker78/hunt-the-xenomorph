#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "command.h"

class GameController {
    private:
        bool continueGame;
        Room* root;
        Alien* alien;
        Ripley* player;
        Item* flamethrower;
        Item* loaderSuit;
        Item* tracker;
        Item* coolantTrap;
        std::map<std::string, Command*> actionMap;
        std::list<Command*> actions;
        void makeMap();
        void addSpecialRoom(Room* specialRoom);
        void addVents();
        void createGame();
        void printActions();
        void sendHints();
        void checkRoom(Room* room, std::string direction, bool notVent);
        void advanceGameState();
    public:
        GameController() : root(nullptr){};
        void startGame();
};

#endif