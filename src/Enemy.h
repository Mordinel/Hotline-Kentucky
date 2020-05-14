#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "TileType.h"
#include "Entity.h"
#include "EnemyState.h"
#include "EnemyType.h"

#define AGGRO_DISTANCE 12.0f

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
