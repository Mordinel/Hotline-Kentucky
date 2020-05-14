/******************************************************************************
 * Filename: TileType.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 29/04/2020
 * Description: Enum containting tile types for both collision and rendering purposes.
 *****************************************************************************/

#ifndef TILETYPE_H
#define TILETYPE_H

enum class TileType {
    Void,
    Unlit,
    Stairs,
    Floor,
    Wall,
    FloorDark,
    WallDark
};

#endif
