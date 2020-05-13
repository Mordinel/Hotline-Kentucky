#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "EntityManager.h"
#include "Enemy.h"
#include "Entity.h"
#include "EnemyState.h"

class EnemyManager : public EntityManager {
    public:
        EnemyManager();
        ~EnemyManager();
        void Draw(sf::RenderWindow* window, const std::vector<std::vector<bool>>& fogOfWar);
        bool Shoot(sf::RectangleShape& rect);
        void DeleteDead();
        void Update(float* deltaTime, sf::Vector2f playerPos);
};

#endif
