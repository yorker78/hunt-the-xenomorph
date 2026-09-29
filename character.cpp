#include "character.h"
#include <set>
#include <tuple>

using namespace std;

list<Room*> Alien::getPathToTrackedRoom() {
    set<Room*> visited;
    list<Room*> basePath;
    basePath.push_back(trackedRoom);
    list<Room*> initial;
    list<tuple<Room*, list<Room*> > > queue;
    queue.push_back(make_tuple(getRoom(), initial));
    while(!queue.empty()) {
        Room* currentRoom = get<0>(queue.front());
        list<Room*> path = get<1>(queue.front());
        queue.pop_front();
        visited.insert(currentRoom);
        if(currentRoom == trackedRoom) {
            return path;
        }
        if(checkVisitedRoom(currentRoom->getNorth(), visited)) {
            list<Room*> northPath(path.begin(), path.end());
            northPath.push_back(currentRoom->getNorth());
            queue.push_back(make_tuple(currentRoom->getNorth(), northPath));
        }
        if(checkVisitedRoom(currentRoom->getEast(), visited)) {
            list<Room*> eastPath(path.begin(), path.end());
            eastPath.push_back(currentRoom->getEast());
            queue.push_back(make_tuple(currentRoom->getEast(), eastPath));
        }
        if(checkVisitedRoom(currentRoom->getSouth(), visited)) {
            list<Room*> southPath(path.begin(), path.end());
            southPath.push_back(currentRoom->getSouth());
            queue.push_back(make_tuple(currentRoom->getSouth(), southPath));
        }
        if(checkVisitedRoom(currentRoom->getWest(), visited)) {
            list<Room*> westPath(path.begin(), path.end());
            westPath.push_back(currentRoom->getWest());
            queue.push_back(make_tuple(currentRoom->getWest(), westPath));
        }
        if(checkVisitedRoom(currentRoom->getVent(), visited)) {
            list<Room*> ventPath(path.begin(), path.end());
            ventPath.push_back(currentRoom->getVent());
            queue.push_back(make_tuple(currentRoom->getVent(), ventPath));
        }
    }
    return basePath;
}

bool Alien::checkVisitedRoom(Room* room, set<Room*> visited) {
    return room != nullptr && visited.find(room) == visited.end();
}
