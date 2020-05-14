/******************************************************************************
 * Filename: Player.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 01/05/2020
 * Description: Handles movement of player and player interaction with the tilemap.
 *****************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#define POWER_UP_TIME 20
#define SPEED_BOOST 1.5f

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "PlayerState.h"

// define Player as child of entity
class Player : public Entity {
public:
    Player(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap);
    void Update(float* deltaTime) override;
    PlayerState GetState();
    void GiveVisibility();
    void GiveSpeed();

private:
    sf::Vector2f lastMovement;
    PlayerState state;
    float powerUpTimeLeft;
};

#endif
