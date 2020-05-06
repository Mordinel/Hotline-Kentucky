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

std::vector<std::vector<TileType>> Dungeon::GenMap() {
    std::vector<std::vector<TileType>> map;

    Box b = getBounds();
    int width = b.right - b.left;
    int height = b.bottom - b.top;
    printf("Got Bound\n");

    // fill map with zeroes/void
    for (int i = 0; i < height; i++) {
        std::vector<TileType> row;

        for (int j = 0; j < width; i ++) {
            row.push_back(TileType::Void);
        }

        map.push_back(row);
    }
    printf("Filled map with zeroes\n");

    printf("Map Size: %d", (int)map.size());

    // fill room tiles;
    for (int i = 0; i < rooms.size(); i++) {
        int x = rooms[i]->X + (b.left * -1);
        int y = rooms[i]->Y + (b.top * -1);
        int right = x + rooms[i]->Width;
        int bottom = y + rooms[i]->Height;

        // fill border with wall tiles
        printf("Made it into loop\n");
        // Top and bottom border
        for (int j = x; j < right; j++) {
            printf("Attempted to create top wall: j:%d y:%d\n", j, y);
            map[y][j] = TileType::Wall;
            printf("Top walls created: j:%d y:%d\n", j, y);
            map[bottom][j] = TileType::Wall;
            printf("Bottom walls created: j:%d y:%d\n", j, y);
        }
        printf("Filled top and bottom border\n");

        // Left and right border
        for (int j = y; j < bottom; j++)
        {
            map[j][x] = TileType::Wall;
            map[j][right] = TileType::Wall;
        }
        printf("Filled left and right border\n");

        // fill inside with floor tiles
        for (int j = y + 1; j < bottom - 1; j++) { // for each row
            // t for tile
            for (int t = x + 1; t < right - 1; t++) { // for each column of row
                map[j][t] = TileType::Floor;
            }
        }
        printf("Filled insides\n");
    }

    printf("About to return map\n");

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

