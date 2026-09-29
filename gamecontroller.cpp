//
// Created by Billy York on 4/1/2024.
//
#include "gamecontroller.h"
#include <vector>

using namespace std;

void GameController::makeMap() {
    root = new EmptyRoom();

    Room* current = root;
    Room* prev;

    //center
    for(int i = 0; i < 4; ++i) {
        current->setEast(new EmptyRoom());
        current->getEast()->setWest(current);
        current = current->getEast();
    }
    //mid top row
    root->getEast()->setNorth(new EmptyRoom());
    current = root->getEast()->getNorth();
    prev = root->getEast();
    for(int i = 0; i < 4; ++i) {
        current->setEast(new EmptyRoom());
        current->getEast()->setWest(current);
        if(prev != nullptr){
            current->setSouth(prev);
            prev->setNorth(current);
            prev = prev->getEast();
        }
        current = current->getEast();
    }
    //top row
    root->getEast()->getEast()->getNorth()->setNorth(new EmptyRoom());
    current = root->getEast()->getEast()->getNorth()->getNorth();
    prev = root->getEast()->getEast()->getNorth();
    for(int i = 0; i < 4; ++i) {
        current->setEast(new EmptyRoom());
        current->getEast()->setWest(current);
        if(prev != nullptr){
            current->setSouth(prev);
            prev->setNorth(current);
            prev = prev->getEast();
        }
        current = current->getEast();
    }
    //mid bottom row
    root->getEast()->setSouth(new EmptyRoom());
    current = root->getEast()->getSouth();
    prev = root->getEast();
    for(int i = 0; i < 4; ++i) {
        current->setEast(new EmptyRoom());
        current->getEast()->setWest(current);
        if(prev != nullptr){
            current->setNorth(prev);
            prev->setSouth(current);
            prev = prev->getEast();
        }
        current = current->getEast();
    }
    //bottom row
    root->getEast()->getEast()->getSouth()->setSouth(new EmptyRoom());
    current = root->getEast()->getEast()->getSouth()->getSouth();
    prev = root->getEast()->getEast()->getSouth();
    for(int i = 0; i < 4; ++i) {
        current->setEast(new EmptyRoom());
        current->getEast()->setWest(current);
        if(prev != nullptr){
            current->setNorth(prev);
            prev->setSouth(current);
            prev = prev->getEast();
        }
        current = current->getEast();
    }

    Room* protoNest = new ProtoNest();
    addSpecialRoom(protoNest);
    alien = new Alien(protoNest);
    //protoNest->setItem(coolantTrap);
    Room* airlock = new Airlock();
    addSpecialRoom(airlock);
    Room* shuttleBay = new ShuttleBay(airlock);
    addSpecialRoom(shuttleBay);
    Room* medBay = new MedBay(protoNest);
    addSpecialRoom(medBay);
    player = new Ripley(medBay);
    Room* cargoBay = new CargoBay(airlock, shuttleBay);
    addSpecialRoom(cargoBay);
    cargoBay->setItem(loaderSuit);

    for(int i = 0; i < 2; i++) {
        addVents(); // Add two pairs of vents between rooms
    }
}

void GameController::addSpecialRoom(Room* specialRoom) {
    Room* roomToReplace;
    if(specialRoom->getY() < 3) {
        roomToReplace = root->getEast()->getNorth()->getEast()->getNorth();
        for(int i = 0; i < specialRoom->getY(); ++i) {
            roomToReplace = roomToReplace->getSouth()->getWest();
        }
    } else {
        roomToReplace = root;
        for(int i = 2; i < specialRoom->getY(); ++i) {
            roomToReplace = roomToReplace->getEast()->getSouth();
        }
    }
    for(int i = 0; i < specialRoom->getX(); ++i) {
        roomToReplace = roomToReplace->getEast();
    }
    if(roomToReplace->getNorth() != nullptr) {
        specialRoom->setNorth(roomToReplace->getNorth());
        roomToReplace->getNorth()->setSouth(specialRoom);
    }
    if(roomToReplace->getSouth() != nullptr) {
        specialRoom->setSouth(roomToReplace->getSouth());
        roomToReplace->getSouth()->setNorth(specialRoom);
    }
    if(roomToReplace->getEast() != nullptr) {
        specialRoom->setEast(roomToReplace->getEast());
        roomToReplace->getEast()->setWest(specialRoom);
    }
    if(roomToReplace->getWest() != nullptr) {
        specialRoom->setWest(roomToReplace->getWest());
        roomToReplace->getWest()->setEast(specialRoom);
    }
    if(roomToReplace->getVent() != nullptr) {
        specialRoom->setVent(roomToReplace->getVent());
        roomToReplace->getVent()->setVent(specialRoom);
    }
    if(specialRoom->getX() == 0 && specialRoom->getY() == 2) {
        root = specialRoom;
    }
    delete roomToReplace;
}

void GameController::addVents() {
    vector<Room*> possibleRooms;
    int x1, y1;
    Room* room1;
    do {
        x1 = rand() % 5;
        y1 = rand() % 5;
        room1 = root;
        if(y1 < 2) {
            for (int i = 0; i < 2 - y1; ++i) {
                room1 = room1->getEast()->getNorth();
            }
        } else if(y1 > 2) {
            for (int i = 0; i < y1 - 2; ++i) {
                room1 = room1->getEast()->getSouth();
            }
        }
        for (int i = 0; i < x1; ++i) {
            room1 = room1->getEast();
        }
    } while (room1->getVent() != nullptr);

    // Fill the list with possible rooms
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            Room* currentRoom = root;
            if (y < 2) {
                for (int i = 0; i < 2 - y; ++i) {
                    currentRoom = currentRoom->getEast()->getNorth();
                }
            } else if (y > 2) {
                for (int i = 0; i < y - 2; ++i) {
                    currentRoom = currentRoom->getEast()->getSouth();
                }
            }
            for (int i = 0; i < x; ++i) {
                currentRoom = currentRoom->getEast();
            }

            //Criteria for being a vent room
            if (currentRoom != room1 && //Can't be the current room or adjacent rooms
                currentRoom->getVent() == nullptr && //Can't already have a vent
                currentRoom->getNorth() != room1 &&
                currentRoom->getSouth() != room1 &&
                currentRoom->getEast() != room1 &&
                currentRoom->getWest() != room1) {
                possibleRooms.push_back(currentRoom);
            }
        }
    }
    Room* room2 = possibleRooms[rand() % possibleRooms.size()];
    room1->setVent(room2);
    room2->setVent(room1);
}

void GameController::sendHints() {
    Room* playerRoom = player->getRoom();
    checkRoom(playerRoom->getNorth(), "to the north", true);
    checkRoom(playerRoom->getSouth(), "to the south", true);
    checkRoom(playerRoom->getEast(), "to the east", true);
    checkRoom(playerRoom->getWest(), "to the west", true);
    checkRoom(playerRoom->getVent(), "through the vent", false);
}

void GameController::checkRoom(Room* room, string direction, bool notVent) {
    if(room != nullptr) {
        if(room == alien->getRoom()) {
            cout << "You hear something creepy " + direction << endl;
        }
        if (ProtoNest* protoNest = dynamic_cast<ProtoNest*>(room)) {
            cout << "You notice a nest in the room " + direction << endl;
        }
        else if (Airlock* airlock = dynamic_cast<Airlock*>(room)) {
            cout << "You notice the airlock " + direction << endl;
        }
        else if (ShuttleBay* shuttleBay = dynamic_cast<ShuttleBay*>(room)) {
            cout << "You notice the shuttle bay " + direction << endl;
        }
        else if (MedBay* medBay = dynamic_cast<MedBay*>(room)) {
            cout << "You hear the hum of medical devices " + direction << endl;
        }
        else if (CargoBay* cargoBay = dynamic_cast<CargoBay*>(room)) {
            cout << "You see cargo " + direction << endl;
        }
        if (room->getVent() != nullptr && notVent) {
            cout << "You hear a rush of air " + direction << endl;
        }
    }
}

void GameController::createGame() {
    srand(time(NULL));
    flamethrower= new Flamethrower();
    loaderSuit = new LoaderSuit();
    tracker = new Tracker();
    coolantTrap = new CoolantTrap();
    makeMap();
    player->addItem(flamethrower);
    //player->addItem(tracker);
    player->addItem(coolantTrap);
    continueGame = true;
    Command* quit = new Quit(&continueGame);
    Command* help = new Help();
    Command* debug = new Debug(root, player, alien);
    Command* north = new North(player);
    Command* south = new South(player);
    Command* east = new East(player);
    Command* west = new West(player);
    Command* vent = new Vent(player);
    Command* flameThrowerCommand = new FlamethrowerCommand(flamethrower, player, alien, &continueGame);
    Command* trackerCommand = new TrackerCommand(tracker, player, alien);
    Command* trapCommand = new CoolantCommand(coolantTrap, player);
    Command* airlockCommand = new AirlockCommand(player, alien, &continueGame);
    actions.push_back(quit);
    actions.push_back(help);
    actions.push_back(debug);
    actions.push_back(north);
    actions.push_back(south);
    actions.push_back(east);
    actions.push_back(west);
    actions.push_back(vent);
    actions.push_back(flameThrowerCommand);
    actions.push_back(trackerCommand);
    actions.push_back(trapCommand);
    actions.push_back(airlockCommand);
    actionMap["q"] = quit;
    actionMap["quit"] = quit;
    actionMap["h"] = help;
    actionMap["help"] = help;
    actionMap["d"] = debug;
    actionMap["debug"] = debug;
    actionMap["n"] = north;
    actionMap["north"] = north;
    actionMap["s"] = south;
    actionMap["south"] = south;
    actionMap["e"] = east;
    actionMap["east"] = east;
    actionMap["w"] = west;
    actionMap["west"] = west;
    actionMap["v"] = vent;
    actionMap["vent"] = vent;
    actionMap["f"] = flameThrowerCommand;
    actionMap["flamethrower"] = flameThrowerCommand;
    actionMap["t"] = trackerCommand;
    actionMap["track"] = trackerCommand;
    actionMap["c"] = trapCommand;
    actionMap["coolant"] = trapCommand;
    actionMap["o"] = airlockCommand;
    actionMap["open"] = airlockCommand;
}

void GameController::startGame() {
    createGame();
    string action;
    bool devModeEnabled = false;
    bool advance = false;
    system("cls");
    while (continueGame) {
        sendHints();
        printActions();
        cin >> action;
        if(devModeEnabled) {
            system("cls");
        }
        for(int i = 0; i < action.size(); ++i) {
            action.at(i) = tolower(action.at(i));
        }
        if(actionMap.find(action) != actionMap.end()) {
            if(action != "d") {
                advance = actionMap[action]->execute();
            } else {
                devModeEnabled = !devModeEnabled;
                system("cls");
            }
            if(advance)
                advanceGameState();
            if(devModeEnabled) {
                cout << endl;
                actionMap["d"]->execute();
                cout << endl;
            }
        } else {
            cout << "I'm sorry, I don't understand. Please try again." << endl;
        }
        if(dynamic_cast<ShuttleBay*>(player->getRoom()) != nullptr && (player->getRoom() != alien->getRoom())) {
            continueGame = false;
            cout << "You made it to the shuttle bay and escaped, leaving someone else to deal with the alien.";
        }
    }
}

void GameController::advanceGameState() {
    alien->setTrackedRoom(player->getRoom());
    if(alien->isAwake()) {
        alien->move(alien->getPathToTrackedRoom().front());
        if(alien->getRoom() == player->getRoom()) {
            continueGame = false;
            cout << "You feel a sharp pain in your chest. The light fades from your vision. The alien has won." << endl;
        }
    } else {
        if(alien->getPathToTrackedRoom().size() <= 2) {
            alien->setAwake(true);
            cout << "You hear a rumbling from deep within the ship. The alien is awake and on the hunt." << endl;
        }
    }
}

void GameController::printActions() {
    cout << "Action: ";
    for(Command* c : actions) {
        c->printCommand();
    }
    cout << endl;
}