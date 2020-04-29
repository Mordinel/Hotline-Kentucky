#include "Dungeon.h"

Dungeon::Dungeon()
{
    roomCount = 10;
    genRooms(roomCount);
}

Dungeon::~Dungeon(){}

void Dungeon::genRooms(unsigned int roomCount) {
    unsigned int r;
    int ri; 
    int newX;
    int newY;
    int newWidth;
    int newHeight;
    bool intersects;
    Room* tmpRoom;

    for (r = 0; r < roomCount; r++) {
        do {
            // generate random room values
            newWidth = (std::rand() % ROOM_MAXSIZE - ROOM_MINSIZE) + ROOM_MINSIZE;
            newHeight = (std::rand() % ROOM_MAXSIZE - ROOM_MINSIZE) + ROOM_MINSIZE;
            newX = std::rand() % (DUNGEON_SIZE - newWidth);
            newY = std::rand() % (DUNGEON_SIZE - newHeight);

            tmpRoom = new Room(newX, newY, newWidth, newHeight);

            intersects = false;
            // check if any of the existing rooms intersect
            for (ri = 0; ri < r; ri ++) {
                intersects = roomsIntersect(tmpRoom, rooms[ri]);
            }

            if (intersects) {
                delete tmpRoom;
            } else {
                rooms.push_back(tmpRoom);
            }

        } while (intersects);
    }

}

bool Dungeon::roomsIntersect(Room* a, Room* b) {
    int deltaX;
    int deltaY;
    int intersectX;
    int intersectY;

    deltaX = b->X - a->X;
    deltaY = b->Y - a->Y;

    intersectX = abs(deltaX) - ((b->Width / 2) + (a->Width / 2));
    intersectY = abs(deltaY) - ((b->Height / 2) + (a->Height / 2));

    return ((intersectX < 0) && (intersectY < 0));
}

void Dungeon::genPaths() {
    
}

void Dungeon::NextDungeon() {
    
}

std::vector<std::vector<int>> Dungeon::GetDungeon() {
    return dungeon;
}

std::vector<Room*> Dungeon::GetRooms()
{
    return rooms;
}
