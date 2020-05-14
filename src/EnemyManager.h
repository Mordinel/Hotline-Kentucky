#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "EntityManager.h"
#include "Enemy.h"
#include "Entity.h"
#include "EnemyState.h"
#include "EnemyType.h"

class EnemyManager : public EntityManager {
    public:
        EnemyManager();
        ~EnemyManager();
        void Draw(sf::RenderWindow* window, const std::vector<std::vector<bool>>& fogOfWar);
        bool Shoot(sf::RectangleShape& rect);
        void DeleteDead();
        void Update(float* deltaTime, sf::Vector2f playerPos);
        bool CheckCollisionPlayer(Entity& ent, float push);
};

#endif
