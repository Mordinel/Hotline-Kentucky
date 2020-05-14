/******************************************************************************
 * Filename: Player.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 01/05/2020
 * Description: Handles player movement, animation and collision with the game world.
 *****************************************************************************/

#include <SFML/Graphics.hpp>

#include "Player.h"

/*
 * Player Constructor
 *
 * Parameters:
 *      texture - the texture for the player
 *      window - the window the player will be drawn to
 *      imageCount - the image count of the texture
 *      switchTime - the speed of the animation transitions
 *      speed - how fast the entity will move
 *      tileMap - a matrix of tileTypes
 */
Player::Player(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap) : Entity(texture, window, imageCount, switchTime, speed, tileMap) {
    row = 7;
    lastMovement.x = 0.0f;
    lastMovement.y = 0.0f;
}

/*
 * Player upater
 * Called every game tick
 * Handles movement, animation, tilemap collisions and powerups
 *
 * Parameters:
 *      deltaTime - determines the distance a player should move and the frame of the animation.
 */
void Player::Update(float* deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);

    // set next movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= speed * *deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += speed * *deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= speed * *deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += speed * *deltaTime;
    }

    if (state == PlayerState::IncreasedSpeed) {
        movement.x *= SPEED_BOOST;
        movement.y *= SPEED_BOOST;
    }

    
    // set sprite sheet row depending on direction
    if (movement.x == 0.0f && movement.y == 0.0f) { // idle

        if (lastMovement.x < 0.0f) {
            row = WEST_IDLE;
        } else if (lastMovement.x > 0.0f) {
            row = EAST_IDLE;
        } else if (lastMovement.y < 0.0f) {
            row = NORTH_IDLE;
        } else if (lastMovement.y > 0.0f) {
            row = SOUTH_IDLE;
        }
        
    } else if (movement.x < 0.0f) { // west
        row = WEST_MOVING;
    } else if (movement.x > 0.0f) { // east
        row = EAST_MOVING;
    } else if (movement.y < 0.0f) { // north
        row = NORTH_MOVING;
    } else if (movement.y > 0.0f) { // south
        row = SOUTH_MOVING;
    }

    lastMovement.x = movement.x;
    lastMovement.y = movement.y;

    animation.Update(row, deltaTime);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
    checkCollisionsNearBody();

    if (state == PlayerState::IncreasedSpeed || state == PlayerState::IncreasedVision) {
        powerUpTimeLeft -= *deltaTime;

        if (powerUpTimeLeft < 0) {
            state = PlayerState::Normal;
        }
    }
}

/*
 * Returns player state.
 */
PlayerState Player::GetState() {
    return state;
}

/*
 * Enables the increased speed powerup.
 */
void Player::GiveSpeed() {
    state = PlayerState::IncreasedSpeed;
    powerUpTimeLeft = POWER_UP_TIME;
}

/*
 * Enables the increasted visibility powerup.
 */
void Player::GiveVisibility() {
    state = PlayerState::IncreasedVision;
    powerUpTimeLeft = POWER_UP_TIME;
}

