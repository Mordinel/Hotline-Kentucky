#include <iostream>
#include "Dungeon.h"
#include "Direction.h"

Dungeon::Dungeon()
{
    roomCount = 32;
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

    // generate roomCount amount of rooms
    for (r = 0; r < roomCount; r++) {
        // generate random room values
        newWidth = (std::rand() % (ROOM_MAXSIZE - ROOM_MINSIZE)) + ROOM_MINSIZE;
        newHeight = (std::rand() % (ROOM_MAXSIZE - ROOM_MINSIZE)) + ROOM_MINSIZE;
       
        // first room always at 0,0
        if (r == 0) {
            newX = 0;
            newY = 0;

            tmpRoom = new Room(newX, newY, newWidth, newHeight);

            rooms.push_back(tmpRoom);
        } else {    // all other rooms except room 0
            do {
                // randomly pick a direction and an existing room
                Direction newDir = (Direction)(std::rand() % (int)Direction::None);
                branchRoom = std::rand() % rooms.size(); 

                // plot the new room based on the direction
                switch (newDir) {
                    case Direction::North:
                        newX = rooms[branchRoom]->GetCenter().x;
                        newY = rooms[branchRoom]->GetCenter().y - (ROOM_MAXSIZE);
                        break;
                    case Direction::East:
                        newX = rooms[branchRoom]->GetCenter().x + (ROOM_MAXSIZE);
                        newY = rooms[branchRoom]->GetCenter().y;
                        break;
                    case Direction::South:
                        newX = rooms[branchRoom]->GetCenter().x;
                        newY = rooms[branchRoom]->GetCenter().y + (ROOM_MAXSIZE);
                        break;
                    case Direction::West:
                        newX = rooms[branchRoom]->GetCenter().x - (ROOM_MAXSIZE);
                        newY = rooms[branchRoom]->GetCenter().y;
                        break;
                }
                

                // instance the new room
                tmpRoom = new Room(newX, newY, newWidth, newHeight);
                tmpRoom->ConnectsTo = rooms[branchRoom];

                intersects = false;

                // check if any of the existing rooms intersect
                for (ri = 0; !intersects && (ri < r); ri++) {
                    intersects = roomsIntersect(tmpRoom, rooms[ri]);
                }

                // if intersects delete room else add it to the room list
                if (intersects) {
                    delete tmpRoom;
                } else {
                    rooms.push_back(tmpRoom);
                }
            } while (intersects); // while intersects
        }
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

std::vector<Room*> Dungeon::GetRooms() {
    return rooms;
}

std::vector<std::vector<int>> Dungeon::GenMap() {
    std::vector<std::vector<int>> map;

    Box b = getBounds();
    
    

    return map;
}

Box Dungeon::getBounds()
{
    int minLeft = 0;
    int minTop = 0;
    int maxRight = 0;
    int maxBottom = 0;

    for (int i = 0; i < rooms.size(); i++)
    {
        int left = rooms[i]->X;
        int top = rooms[i]->Y;
        int right = left + rooms[i]->Width;
        int bottom = top + rooms[i]->Height;

        if (left < minLeft) {
            minLeft = left;
        }
        if (top < minTop) {
            minTop = top;
        }
        if (right > maxRight) {
            maxRight = right;
        }
        if (bottom > maxBottom) {
            maxBottom = bottom;
        }
    }

    Box bounds;
    bounds.left = minLeft;
    bounds.top = minTop;
    bounds.right = maxRight;
    bounds.bottom = maxBottom;
    
    return bounds;
}

