//
// Created by Billy York on 4/11/2024.
//

#ifndef HUNT_THE_XENOMORPH_COMMAND_H
#define HUNT_THE_XENOMORPH_COMMAND_H

#include "character.h"
#include <algorithm>
#include <map>

class Command {
    protected:
        std::string commandString;
        virtual bool isAllowed() = 0;
    public:
        explicit Command(const std::string &commandString) {this->commandString = commandString;};
        virtual ~Command() = default;
        virtual bool execute() = 0;
        virtual void printCommand() { if(isAllowed()) std::cout << commandString;};
};

class Quit : public Command {
    private:
        bool* continueGame;
        bool isAllowed() override {return true;}
    public:
        explicit Quit(bool* continueGame) : Command("Q)uit "), continueGame(continueGame) {};
        bool execute() override {std::cout << "Goodbye!"; *continueGame = false; return false;}
};

class Help : public Command {
    private:
        bool isAllowed() override {return  true;}
    public:
        Help() : Command("H)elp ") {};
        bool execute() override {
            std::cout << "Priority one Insure return of organism for analysis. All other considerations secondary. Crew expendable." << std::endl << std::endl;
            std::cout << "You are Ripley, the last remaining survivor of the Nostromo. Your goal is to escape the Xenomorph through any means necessary." << std::endl;
            std::cout << "You can find items and means of escape throughout the ship. The Xenomorph, once awoken, will be on the hunt for you." << std::endl;
            std::cout << "Use your flamethrower and clever map maneuvering to defeat the Xenomorph" << std::endl << std::endl;
            std::cout << "A list of commands will appear. You can type the letter inside the parentheses to do that command" << std::endl;
            return false;
        }
};

class Debug : public Command {
    private:
        Room* root;
        Character* ripley;
        Character* alien;
        bool isAllowed() override {return true;}
    public:
        Debug(Room* root, Character* ripley, Character* alien) : Command(""), root(root), ripley(ripley), alien(alien) {};
        bool execute() override;
};

class North : public Command {
    private:
        Character* character;
        bool isAllowed() override { return character->getRoom()->getNorth() != nullptr;}
    public:
        explicit North(Character* character) : Command("N)orth "), character(character) {};
        bool execute() override {
            if(isAllowed()){
                character->move(character->getRoom()->getNorth());
                return true;
            }
            return false;
        };
};

class South : public Command {
    private:
        Character* character;
        bool isAllowed() override {return character->getRoom()->getSouth() != nullptr;};
    public:
        explicit South(Character* character) : Command("S)outh "), character(character) {};
        bool execute() override {
            if(isAllowed()) {
                character->move(character->getRoom()->getSouth());
                return true;
            }
            return false;
        };
};

class East : public Command {
    private:
        Character* character;
        bool isAllowed() {return character->getRoom()->getEast() != nullptr;};
    public:
        East(Character* character) : Command("E)ast "), character(character) {};
        bool execute() {
            if(isAllowed()) {
                character->move(character->getRoom()->getEast());
                return true;
            }
            return false;
        };
};

class West : public Command {
    private:
        Character* character;
        bool isAllowed() {return character->getRoom()->getWest() != nullptr;};
    public:
        West(Character* character) : Command("W)est "), character(character) {};
        bool execute() {
            if(isAllowed()) {
                character->move(character->getRoom()->getWest());
                return true;
            }
            return false;
        };
};

class Vent : public Command {
    private:
        Character* character;
        bool isAllowed() {return character->getRoom()->getVent() != nullptr;};
    public:
        Vent(Character* character) : Command("V)ent "), character(character) {};
        bool execute() {
            if(isAllowed()) {
                character->move(character->getRoom()->getVent());
                return true;
            }
            return false;
        };
};

class FlamethrowerCommand : public Command {
    private:
        Item* flamethrower;
        Ripley* ripley;
        Character* alien;
        bool* continueGame;
        bool isAllowed() {
            bool hasItem = false;
            for(Item* i : ripley->getItems()) {
                if(i == flamethrower)
                    hasItem = true;
            }
            return hasItem && flamethrower->usable();
        }
    public:
        FlamethrowerCommand(Item* flamethrower, Ripley* ripley, Character* alien, bool* continueGame) : Command("F)lamethrower "), flamethrower(flamethrower), ripley(ripley), alien(alien), continueGame(continueGame) {};
        bool execute();
};

class TrackerCommand : public Command {
    private:
        Item* tracker;
        Ripley* ripley;
        Character* alien;
        bool isAllowed() {
            bool hasItem = false;
            for(Item* i : ripley->getItems()) {
                if(i == tracker)
                    hasItem = true;
            }
            return hasItem && tracker->usable();
        }
        void trackRoom(Room* room);
    public:
        TrackerCommand(Item* tracker, Ripley* ripley, Character* alien) : Command("T)rack the alien "), tracker(tracker), ripley(ripley), alien(alien) {};
        bool execute();
};

class CoolantCommand : public Command {
    private:
        Item* coolantTrap;
        Ripley* ripley;
        bool isAllowed() {
            bool hasItem = false;
            for(Item* i : ripley->getItems()) {
                if(i == coolantTrap)
                    hasItem = true;
            }
            return hasItem && coolantTrap->usable();
        };
    public:
        CoolantCommand(Item *coolantTrap, Ripley *ripley)
                : Command("C)oolant trap the room "), coolantTrap(coolantTrap), ripley(ripley) {};
        bool execute();
};

class AirlockCommand : public Command {
private:
    Ripley* ripley;
    Airlock* airlock{};
    Character* alien;
    bool* continueGame;

    bool isAllowed() override {
        Room* currentRoom = ripley->getRoom();
        airlock = nullptr;
        if(dynamic_cast<Airlock*>(currentRoom) != nullptr && dynamic_cast<Airlock*>(currentRoom)->getCanBeOpened()) {
            airlock = dynamic_cast<Airlock*>(currentRoom);
        } else if(dynamic_cast<Airlock*>(currentRoom->getNorth()) != nullptr && dynamic_cast<Airlock*>(currentRoom->getNorth())->getCanBeOpened()) {
            airlock = dynamic_cast<Airlock*>(currentRoom->getNorth());
        } else if(dynamic_cast<Airlock*>(currentRoom->getSouth()) != nullptr && dynamic_cast<Airlock*>(currentRoom->getSouth())->getCanBeOpened()) {
            airlock = dynamic_cast<Airlock*>(currentRoom->getSouth());
        } else if(dynamic_cast<Airlock*>(currentRoom->getEast()) != nullptr && dynamic_cast<Airlock*>(currentRoom->getEast())->getCanBeOpened()) {
            airlock = dynamic_cast<Airlock*>(currentRoom->getEast());
        } else if(dynamic_cast<Airlock*>(currentRoom->getWest()) != nullptr && dynamic_cast<Airlock*>(currentRoom->getWest())->getCanBeOpened()) {
            airlock = dynamic_cast<Airlock*>(currentRoom->getWest());
        }
        return airlock != nullptr;
    };
public:
    AirlockCommand(Ripley* ripley, Character* alien, bool* continueGame) : Command("O)pen the airlock "), ripley(ripley), alien(alien), continueGame(continueGame) {};
    bool execute() override;
};

#endif //HUNT_THE_XENOMORPH_COMMAND_H
