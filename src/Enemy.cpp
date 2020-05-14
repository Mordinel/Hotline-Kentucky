/******************************************************************************
 * Filename: Enemy.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 10/04/2020
 * Description: Class representing an enemy in the game
 *****************************************************************************/

#include "Enemy.h"

/*
 * Enemy Constructor
 *
 * Parameters:
 *      texture - the texture for the enemy
 *      window - the window the enemy will be drawn to
 *      imageCount - the image count of the texture
 *      switchTime - the speed of the animation transitions
 *      speed - the speed of the enemy
 *      tileMap - a matrix of tileTypes
 *      itemType- the type of item
 */
Enemy::Enemy(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap, EnemyType type) : Entity(texture, window, imageCount, switchTime, speed, tileMap) {
    state = EnemyState::Wander;
    lastMovement = sf::Vector2f(0.0f, 0.0f);
    this->type = type;

    if (type == EnemyType::Mecha) {
        body.setSize(sf::Vector2f(48.0f, 48.0f));
    }
}

/*
 * Sets the enemy's state to dead
 */
void Enemy::Die() {
    this->state = EnemyState::Dead;
}

/*
 * Updates the enemy
 *
 * Parameters:
 *      deltaTime - time passed since last game loop
 *      playerPos - the position of the player used for the "AI"
 */
void Enemy::Update(float* deltaTime, sf::Vector2f playerPos) {
    float xMove = 0.0f;
    float yMove = 0.0f;

    // different AI based on different types
    switch(type) {
        case EnemyType::Evil:
            evilUpdate(playerPos, xMove, yMove);
            break;
        case EnemyType::Mecha:
            mechaUpdate(playerPos, xMove, yMove);
            break;
        case EnemyType::Good:
            goodUpdate(xMove, yMove);
            break;
    }

    // apply AI movement
    sf::Vector2f movement(xMove, yMove);

    if (movement.x == 0.0f && movement.y == 0.0f) { // idle
        if (lastMovement.x < 0.0f) {
            row = 4;
        } else if (lastMovement.x > 0.0f) {
            row = 5;
        } else if (lastMovement.y < 0.0f) {
            row = 6;
        } else if (lastMovement.y > 0.0f) {
            row = 7;
        }   
    } else if (movement.x < 0.0f) { // west
        row = 0;
    } else if (movement.x > 0.0f) { // east
        row = 1;
    } else if (movement.y < 0.0f) { // north
        row = 2;
    } else if (movement.y > 0.0f) { // south
        row = 3;
    }
    
    animation.Update(row, deltaTime);
    body.setTextureRect(animation.uvRect);
    body.move(movement);

    lastMovement = movement;

    checkCollisionsNearBody();
}

/*
 * Updates the mecha type enemy
 *
 * Parameters:
 *      playerPos - the position of the player
 *      xMove - the amount the enemy should move in the x direction
 *      yMove - the amount the enemy should move in the y direction
 */
void Enemy::mechaUpdate(sf::Vector2f& playerPos, float& xMove, float& yMove) {
    if (GetDistanceBetween(playerPos) < AGGRO_DISTANCE * 32.0f) {
        state = EnemyState::Attack;
    }

    if (state == EnemyState::Wander) {
        wander(xMove, yMove);   
    } else if (state == EnemyState::Attack) {
        walkAttack(playerPos, xMove, yMove);
    }
}

/*
 * Updates the evil type enemy
 *
 * Parameters:
 *      playerPos - the position of the player
 *      xMove - the amount the enemy should move in the x direction
 *      yMove - the amount the enemy should move in the y direction
 */
void Enemy::evilUpdate(sf::Vector2f& playerPos, float& xMove, float& yMove) {
    if (GetDistanceBetween(playerPos) < AGGRO_DISTANCE * 32.0f) {
        state = EnemyState::Attack;
    }

    if (state == EnemyState::Wander) {
        wander(xMove, yMove);   
    } else if (state == EnemyState::Attack) {
        walkAttack(playerPos, xMove, yMove);
    }
}

/*
 * Updates the good type enemy
 *
 * Parameters:
 *      xMove - the amount the enemy should move in the x direction
 *      yMove - the amount the enemy should move in the y direction
 */
void Enemy::goodUpdate(float& xMove, float& yMove) {
    if (state == EnemyState::Wander) {
        wander(xMove, yMove);
    }
}


/*
 * Makes the enemy wander in a random direction
 *
 * Parameters:
 *      xMove - the amount the enemy should move in the x direction
 *      yMove - the amount the enemy should move in the y direction
 */
void Enemy::wander(float& xMove, float& yMove) {
     if (std::rand() % 10 == 1) {
        int xDirection = std::rand() % 2;
        int yDirection = std::rand() % 2;

        if (xDirection == 0) {
            xMove = speed;
        } else {
            xMove = speed * -1;
        }
        if (yDirection == 0) {
            yMove = speed;
        } else {
            yMove = speed * -1;
        }
    }   
}

/*
 * Updates the good type enemy
 *
 * Parameters:
 *      xMove - the amount the enemy should move in the x direction
 *      yMove - the amount the enemy should move in the y direction
 */
void Enemy::walkAttack(sf::Vector2f& playerPos, float& xMove, float& yMove) {
    sf::Vector2f currentPos = body.getPosition();
    sf::Vector2f deltaPos = playerPos - currentPos;

    if (deltaPos.x > 0 && deltaPos.x < 16) {
        xMove = 0;
    } else if (deltaPos.x > 0) {
        xMove = speed;
    } else {
        xMove = speed * -1;
    }

    if (deltaPos.y > 0 && deltaPos.y < 16) {
        yMove = 0;
    } else if (deltaPos.y > 0) {
        yMove = speed;
    } else {
        yMove = speed * -1;
    }
}

