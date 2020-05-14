/******************************************************************************
 * Filename: PlayerState.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 14/05/2020
 * Description: An enum that describes the players current condition/state.
 *****************************************************************************/

#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

enum class PlayerState {
    Normal,
    IncreasedVision,
    IncreasedSpeed,
    Dead
};

#endif