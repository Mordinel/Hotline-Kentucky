#ifndef DUNGEON_H
#define DUNGEON_H

#include <cstdlib>
#include <vector>

//#include "TileType.h"
#include "Room.h"

#define DUNGEON_SIZE 100
#define ROOM_MAXSIZE 30
#define ROOM_MINSIZE 10
#define MIN_ROOM_COUNT 2;
#define CORRIDOR_WIDTH 3

class Dungeon {
private:    
    std::vector<std::vector<int>> dungeon;
    std::vector<Room*> rooms;
    unsigned int roomCount;

    void genRooms(unsigned int roomCount);
    bool roomsIntersect(Room* a, Room* b);
    void genPaths();
public:
    Dungeon();
    ~Dungeon();

    void NextDungeon();
    std::vector<std::vector<int>> GetDungeon();
    std::vector<Room*> GetRooms();
};

#endif
