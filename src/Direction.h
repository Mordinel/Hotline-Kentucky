/******************************************************************************
 * Filename: Direction.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 01/05/2020
 * Description: Enum containing directions. Used by Dungeon class to randomly pick a direction for new rooms.
 *****************************************************************************/

#ifndef DIRECTION_H
#define DIRECTION_H

enum class Direction {
    North,
    East,
    South,
    West,
    None
};

#endif
