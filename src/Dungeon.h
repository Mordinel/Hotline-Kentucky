#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>
#include <cstdlib>
#include <vector>

#include "TileType.h"
#include "Room.h"
#include "Box.h"

#define ROOM_MAXSIZE 18
#define ROOM_MINSIZE 10
#define MIN_ROOM_COUNT 2
#define CORRIDOR_WIDTH 3
#define INITIAL_ROOM_COUNT 6
#define ROOM_INCREASE 3

class Dungeon {
private:    
    std::vector<Room*> rooms;
    unsigned int roomCount;

    void genRooms(unsigned int roomCount);
    bool roomsIntersect(Room* a, Room* b);
    Box getBounds();
    void translateRooms();
    void clearRooms();

public:
    Dungeon();
    ~Dungeon();

    void NextDungeon();
    std::vector<Room*> GetRooms();
    std::vector<std::vector<TileType>> GenMap();
};

#endif
