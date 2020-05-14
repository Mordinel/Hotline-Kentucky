/******************************************************************************
 * Filename: Box.h
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 06/05/2020
 * Description: Simple struct that contains the positions of each side of a box or square shape. Useful for finding the bounds of an area.
 *              Left being the left most x position.
 *              Top  being the top most y position.
 *              Right being the right most x position.
 *              Bottom being the bottom most y position.
 *****************************************************************************/

#ifndef BOX_H
#define BOX_H

struct Box {
    int Left;
    int Top;
    int Right;
    int Bottom;
};

#endif
