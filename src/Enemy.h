/******************************************************************************
 * Filename: Enemy.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 10/04/2020
 * Description: Class representing an enemy in the game
 *****************************************************************************/

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "TileType.h"
#include "Entity.h"
#include "EnemyState.h"
#include "EnemyType.h"

#define AGGRO_DISTANCE 12.0f
#define CHASE_THRESHOLD 16.0f
#define MECHA_SIZE 48.0f
#define TILE_SIZE 32.0f
#define WANDER_CHANCE 10

class Enemy : public Entity {
private:
    EnemyState state;
    EnemyType type;
    sf::Vector2f startLocation;
    sf::Vector2f lastMovement;

    void evilUpdate(sf::Vector2f& playerPos, float& xMove, float& yMove);
    void mechaUpdate(sf::Vector2f& playerPos, float& xMove, float& yMove);
    void goodUpdate(float& xMove, float& yMove);

    void wander(float& xMove, float& yMove);
    void walkAttack(sf::Vector2f& playerPos, float& xMove, float& yMove);

public:
    Enemy(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap, EnemyType type);
    void Die();
    void Update(float* deltaTime, sf::Vector2f playerPos);

    EnemyState GetState() {
        return this->state;
    }

    EnemyType GetType() {
        return this->type;
    }
};

#endif
