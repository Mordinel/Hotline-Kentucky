#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "TileType.h"
#include "Entity.h"
#include "EnemyState.h"

class Enemy : public Entity {
private:
    EnemyState state;
    sf::Vector2f startLocation;
    sf::Vector2f lastMovement;
public:
    Enemy(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap);
    void Die();
    void Update(float* deltaTime, sf::Vector2f playerPos);

    EnemyState GetState() {
        return this->state;
    }
};

#endif
