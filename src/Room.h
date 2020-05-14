/******************************************************************************
 * Filename: Room.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 29/04/2020
 * Description: Data structure for dungeon room generation process.
 *****************************************************************************/

#ifndef ROOM_H
#define ROOM_H

#include <SFML/Graphics.hpp>

class Room {
public:
    Room(int x, int y, int width, int height);
    sf::Vector2f GetCenter();

    int X;
    int Y;
    int Width;
    int Height;
    Room* ConnectsTo;
};

#endif
