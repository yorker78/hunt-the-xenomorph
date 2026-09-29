//
// Created by Billy York on 4/11/2024.
//
#include "command.h"

using namespace std;

bool Debug::execute() {
    Room* rowHead = root->getEast()->getNorth()->getEast()->getNorth();
    Room* currentRoom = rowHead;
    int row = 0;
    cout << "  ";
    while(currentRoom != nullptr){
        if(ripley->getRoom() == currentRoom) {
            cout << "R";
        } else if (alien->getRoom() == currentRoom){
            cout << "X";
        } else {
            currentRoom->print();
        }
        currentRoom = currentRoom->getEast();
        if(currentRoom == nullptr) {
            if(row < 2) {
                rowHead = rowHead->getSouth()->getWest();
            } else {
                rowHead = rowHead->getEast()->getSouth();
            }
            currentRoom = rowHead;
            ++row;
            cout << endl;
            if(row < 5){
                string offset(abs(2-row), ' ');
                cout << offset;
            }
        }
    }
    return false;
}

bool FlamethrowerCommand::execute() {
    if(!isAllowed()) {
        return false;
    }
    flamethrower->use();
    string direction;
    cout << "Where do you want to fire?" << endl;
    if(ripley->getRoom()->getNorth() != nullptr) {
        cout << "N)orth ";
    }
    if(ripley->getRoom()->getSouth() != nullptr) {
        cout << "S)outh ";
    }
    if(ripley->getRoom()->getEast() != nullptr) {
        cout << "E)ast ";
    }
    if(ripley->getRoom()->getWest() != nullptr) {
        cout << "W)est ";
    }
    cout << endl;
    cin >> direction;
    for(int i = 0; i < direction.length(); ++i) {
        direction.at(i) = tolower(direction.at(i));
    }

    bool north = direction == "n" && ripley->getRoom()->getNorth() == alien->getRoom();
    bool south = direction == "s" && ripley->getRoom()->getSouth() == alien->getRoom();
    bool east = direction == "e" && ripley->getRoom()->getEast() == alien->getRoom();
    bool west = direction == "w" && ripley->getRoom()->getWest() == alien->getRoom();

    if(north || south || east || west) {
        *continueGame = false;
        cout << "You toast the alien to a crisp and survive!" << endl;
        return false;
    } else {
        cout << "You fire the flamethrower and only burn through the oxygen on your ship" << endl;
    }
    return true;
}

bool TrackerCommand::execute() {
    if(!isAllowed()){
        return false;
    }
    tracker->use();
    Room* room;
    //top row
    if(ripley->getRoom()->getNorth() != nullptr && ripley->getRoom()->getNorth()->getNorth() != nullptr) {
        room = ripley->getRoom()->getNorth()->getNorth();
        cout << "  ";
        trackRoom(room);
        cout << endl;
    }
    //mid top row
    if(ripley->getRoom()->getNorth() != nullptr && ripley->getRoom()->getNorth()->getWest() != nullptr) {
        room = ripley->getRoom()->getNorth()->getWest();
        cout << " ";
        trackRoom(room);
        trackRoom(room->getEast());
        if(room->getEast()->getEast() != nullptr) {
            trackRoom(room->getEast()->getEast());
        }
        cout << endl;
    } else if(ripley->getRoom()->getNorth() != nullptr) {
        room = ripley->getRoom()->getNorth();
        cout << "  ";
        trackRoom(room);
        if(room->getEast() != nullptr) {
            trackRoom(room->getEast());
        }
        cout << endl;
    } else if(ripley->getRoom()->getEast() != nullptr && ripley->getRoom()->getEast()->getNorth() != nullptr) {
        room = ripley->getRoom()->getEast()->getNorth();
        cout << "   ";
        trackRoom(room);
        cout << endl;
    } else if(ripley->getRoom()->getWest() != nullptr && ripley->getRoom()->getWest()->getNorth() != nullptr) {
        room = ripley->getRoom()->getWest()->getNorth();
        cout << " ";
        trackRoom(room);
        cout << endl;
    }
    //mid row
    if(ripley->getRoom()->getWest() != nullptr && ripley->getRoom()->getWest()->getWest() != nullptr) {
        room = ripley->getRoom()->getWest()->getWest();
        trackRoom(room);
        room = room->getEast();
        trackRoom(room);
        room = room->getEast();
        trackRoom(room);
        room = room->getEast();
        if(room != nullptr) {
            trackRoom(room);
            room = room->getEast();
            if(room != nullptr) {
                trackRoom(room);
            }
        }
        cout << endl;
    } else if(ripley->getRoom()->getWest() != nullptr) {
        cout << " ";
        room = ripley->getRoom()->getWest();
        trackRoom(room);
        room = room->getEast();
        trackRoom(room);
        room = room->getEast();
        if(room != nullptr) {
            trackRoom(room);
            room = room->getEast();
            if(room != nullptr) {
                trackRoom(room);
            }
        }
        cout << endl;
    //If both wests are null, then both easts are guaranteed to not be null.
    } else {
        cout << "  ";
        room = ripley->getRoom();
        trackRoom(room);
        trackRoom(room->getEast());
        trackRoom(room->getEast()->getEast());
        cout << endl;
    }
    //mid bottom row
    if(ripley->getRoom()->getSouth() != nullptr && ripley->getRoom()->getSouth()->getWest() != nullptr) {
        cout << " ";
        room = ripley->getRoom()->getSouth()->getWest();
        trackRoom(room);
        trackRoom(room->getEast());
        room = room->getEast()->getEast();
        if(room != nullptr) {
            trackRoom(room);
        }
        cout << endl;
    } else if (ripley->getRoom()->getSouth() != nullptr) {
        cout << "  ";
        room = ripley->getRoom()->getSouth();
        trackRoom(room);
        room = room->getEast();
        if(room != nullptr) {
            trackRoom(room);
        }
        cout << endl;
    } else if (ripley->getRoom()->getEast() != nullptr && ripley->getRoom()->getEast()->getSouth() != nullptr){
        cout << "   ";
        room = ripley->getRoom()->getEast()->getSouth();
        trackRoom(room);
        cout << endl;
    } else if (ripley->getRoom()->getWest() != nullptr && ripley->getRoom()->getWest()->getSouth() != nullptr){
        cout << " ";
        room = ripley->getRoom()->getWest()->getSouth();
        trackRoom(room);
        cout << endl;
    }
    //bottom row
    if(ripley->getRoom()->getSouth() != nullptr && ripley->getRoom()->getSouth()->getSouth() != nullptr) {
        cout << "  ";
        trackRoom(ripley->getRoom()->getSouth()->getSouth());
        cout << endl;
    }
    return true;
}

void TrackerCommand::trackRoom(Room* room) {
    if(room == alien->getRoom()) {
        cout << "X";
    } else if(room == ripley->getRoom()) {
        cout << "R";
    } else {
        room->print();
    }
}

bool CoolantCommand::execute() {
    if(!isAllowed()) {
        return false;
    }
    coolantTrap->use();
    ripley->getRoom()->setTrap(true);
    cout << "You set the trap and hope its enough to slow down your pursuer" << endl;
    return true;
}

bool AirlockCommand::execute() {
    airlock->setCanBeOpened(false);
    if(ripley->getRoom() == airlock) {
        cout << "You mistakenly open the airlock and eject yourself. At least the alien didn't get you." << endl;
        *continueGame = false;
        return false;
    } else if(alien->getRoom() == airlock) {
        cout << "You open the airlock and successfully eject the alien!" << endl;
        *continueGame = false;
        return false;
    } else {
        cout << "You open the airlock, but the alien wasn't in the room." << endl;
    }
    return true;
}