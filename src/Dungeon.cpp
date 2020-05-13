/******************************************************************************
 * Filename: .cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 29/04/2020
 * Description: Entry point of the program. Creates and runs the game loop.
 *****************************************************************************/

#include <iostream>
#include "Dungeon.h"
#include "Direction.h"

Dungeon::Dungeon()
{
    roomCount = INITIAL_ROOM_COUNT;
    genRooms(roomCount);
    translateRooms();
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

void Dungeon::clearRooms() {
    for (int i = 0; i < roomCount; i++)
    {
        rooms.erase(rooms.begin());
    }
}

void Dungeon::NextDungeon() {
    clearRooms();
    roomCount += ROOM_INCREASE;
    genRooms(roomCount);
    translateRooms();
}

std::vector<Room*> Dungeon::GetRooms() {
    return rooms;
}

std::vector<std::vector<TileType>> Dungeon::GenMap() {
    int i;
    int j;
    int t;
    int d;
    std::vector<std::vector<TileType>> map;

    Box b = getBounds();
    int width = abs(b.Left - b.Right);
    int height = abs(b.Bottom - b.Top);

    // fill map with zeroes/void
    for (i = 0; i < height; i++) {
        std::vector<TileType> row;

        for (int j = 0; j < width; j++) {
            row.push_back(TileType::Void);
        }

        map.push_back(row);
    }

    // fill room tiles;
    for (i = 0; i < rooms.size(); i++) {
        int x = rooms[i]->X + abs(b.Left);
        int y = rooms[i]->Y + abs(b.Top);
        int right = x + rooms[i]->Width;
        int bottom = y + rooms[i]->Height;

        // fill border with wall tiles
        // Top and bottom border
        for (j = x; j < right; j++) {
            map[y][j] = TileType::Wall;
            map[bottom - 1][j] = TileType::Wall;
        }

        // Left and right border
        for (j = y; j < bottom; j++)
        {
            map[j][x] = TileType::Wall;
            map[j][right - 1] = TileType::Wall;
        }

        // fill inside with floor tiles
        for (j = y + 1; j < bottom - 1; j++) { // for each row
            // t for tile
            for (t = x + 1; t < right - 1; t++) { // for each column of row
                map[j][t] = TileType::Floor;
            }
        }
    }

    // fill paths between rooms
    for (i = 1; i < rooms.size(); i++) {
        sf::Vector2f fromPos = rooms[i]->GetCenter();
        sf::Vector2f toPos = rooms[i]->ConnectsTo->GetCenter();
        
        Box path;
        path.Top = (toPos.y < fromPos.y) ? toPos.y : fromPos.y;
        path.Bottom = (toPos.y > fromPos.y) ? toPos.y : fromPos.y;
        path.Left = (toPos.x < fromPos.x) ? toPos.x : fromPos.x;
        path.Right = (toPos.x > fromPos.x) ? toPos.x : fromPos.x;

        path.Top -= 1;
        //path.Bottom += 1;
        path.Left -= 1;
        //path.Right += 1;

        // fill with floor
        for (j = path.Top; j <= path.Bottom; j++) {
            for (t = path.Left; t <= path.Right; t++) {
                map[j][t] = TileType::Floor;
                
                // set adjacent void tiles to walls
                if (map[j+1][t] == TileType::Void) {
                    map[j+1][t] = TileType::Wall;
                }
                if (map[j][t+1] == TileType::Void) {
                    map[j][t+1] = TileType::Wall;
                }
                if (map[j-1][t] == TileType::Void) {
                    map[j-1][t] = TileType::Wall;
                }
                if (map[j][t-1] == TileType::Void) {
                    map[j][t-1] = TileType::Wall;
                }
            }
        }
    }

    sf::Vector2f lastRoomCenter = GetExitLocation();
    map[lastRoomCenter.y][lastRoomCenter.x] = TileType::Stairs;

    return map;
}

sf::Vector2f Dungeon::GetExitLocation() {
    return rooms[rooms.size()-1]->GetCenter();
}

void Dungeon::translateRooms() {
    int i;
    Box b = getBounds();

    for (i = 0; i < rooms.size(); i++) {
        rooms[i]->X = rooms[i]->X + abs(b.Left);
        rooms[i]->Y = rooms[i]->Y + abs(b.Top);
    }
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
    bounds.Left = minLeft;
    bounds.Top = minTop;
    bounds.Right = maxRight;
    bounds.Bottom = maxBottom;
    
    return bounds;
}