/******************************************************************************
 * Filename: EnemyManager.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 12/05/2020
 * Description: Manages collections of enemies, implementing Enemy specific functions.
 *****************************************************************************/

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
        std::vector<Enemy*>* GetDead();
};

#endif
