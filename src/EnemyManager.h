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
        void Shoot(sf::RectangleShape& rect);
        void DeleteDead();
};

#endif
