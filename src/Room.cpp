/******************************************************************************
 * Filename: Room.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 29/04/2020
 * Description: Data structure for dungeon room generation.
 *****************************************************************************/

#include <iostream>

#include "Room.h"

/*
 * Constructor for Room class
 *
 * Parameters:
 *      x - X coordinate
 *      y - Y coordinate
 *      width - room width
 *      height - room height
 */
Room::Room(int x, int y, int width, int height) {
    this->X = x - width / 2;
    this->Y = y - height / 2;
    this->Width = width;
    this->Height = height;
    this->ConnectsTo = nullptr; // not connected to anything
}

/*
 * Gets the coordinates to the center of the room
 * 
 * Returns:
 *      A coordinate vector
 */
sf::Vector2f Room::GetCenter() {
    sf::Vector2f center(X + Width / 2.0f, Y + Height / 2.0f);
    return center;
}

