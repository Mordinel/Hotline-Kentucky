#include <iostream>
#include "Dungeon.h"
#include "Direction.h"

Dungeon::Dungeon()
{
    roomCount = 64;
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
    int branchRoom;
    bool intersects;
    Room* tmpRoom;

    int dungeonSize = roomCount * ROOM_MAXSIZE;

    for (r = 0; r < roomCount; r++) {
        // generate random room values
        newWidth = (std::rand() % (ROOM_MAXSIZE - ROOM_MINSIZE)) + ROOM_MINSIZE;
        newHeight = (std::rand() % (ROOM_MAXSIZE - ROOM_MINSIZE)) + ROOM_MINSIZE;
       
        if (r == 0) {
            newX = 0;
            newY = 0;

            tmpRoom = new Room(newX, newY, newWidth, newHeight);

            rooms.push_back(tmpRoom);
            printf("Initial Room: X:%d Y:%d W:%d H:%d\n", newX, newY, newWidth, newHeight);
        } else {
            do {
                Direction newDir = (Direction)(std::rand() % (int)Direction::None);
                branchRoom = std::rand() % rooms.size(); 
                printf("Branching from room %d\n", branchRoom);
                switch (newDir) {
                    case Direction::North:
                        newX = rooms[branchRoom]->X;
                        newY = rooms[branchRoom]->Y - (ROOM_MAXSIZE);
                        break;
                    case Direction::East:
                        newX = rooms[branchRoom]->X + (ROOM_MAXSIZE);
                        newY = rooms[branchRoom]->Y;
                        break;
                    case Direction::South:
                        newX = rooms[branchRoom]->X;
                        newY = rooms[branchRoom]->Y + (ROOM_MAXSIZE);
                        break;
                    case Direction::West:
                        newX = rooms[branchRoom]->X - (ROOM_MAXSIZE);
                        newY = rooms[branchRoom]->Y;
                        break;
                }
                
                printf("Tried to create room at X:%d Y:%d W:%d H:%d\n", newX, newY, newWidth, newHeight);

                tmpRoom = new Room(newX, newY, newWidth, newHeight);

                intersects = false;

                // check if any of the existing rooms intersect
                for (ri = 0; !intersects && (ri < r); ri++) {
                    intersects = roomsIntersect(tmpRoom, rooms[ri]);
                }

                if (intersects) {
                    printf("New room intersects with room %d\n", ri-1);
                    delete tmpRoom;
                } else {
                    printf("Added room to list\n");
                    rooms.push_back(tmpRoom);
                }
            } while (intersects);
        }
        printf("Added room %d\n", r);
    }
}

bool Dungeon::roomsIntersect(Room* a, Room* b) {
    int deltaX;
    int deltaY;
    int intersectX;
    int intersectY;

    deltaX = b->X - a->X;
    deltaY = b->Y - a->Y;

    intersectX = (abs(deltaX) * 2) - (b->Width + a->Width);
    intersectY = (abs(deltaY) * 2) - (b->Height + a->Height);

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
