/******************************************************************************
 * Filename: EnemyManager.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 12/05/2020
 * Description: Manages collections of enemies, implementing Enemy specific functions.
 *****************************************************************************/

#include "EnemyManager.h"

/*
 * EnemyManager Constructor
 */
EnemyManager::EnemyManager() : EntityManager() {

}

/*
 * EnemyManager Destructor
 */
EnemyManager::~EnemyManager() {

}

/*
 * Calls draw on each item in collection of enemy
 *
 * Parameters:
 *      window - the window to be drawn to
 *      fogOfWar - the matrix to determine whether or not to render enemies.
 */
void EnemyManager::Draw(sf::RenderWindow* window, const std::vector<std::vector<bool>>& fogOfWar) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        entityList[i]->Draw(window, fogOfWar);
    }
}

/*
 * calls shoot on each enemy in collection, calling Die() on the enemy if the rectangle collides.
 *
 * Parameters:
 *      rect - A point along the bullet ray to be checked for collisions.
 */
bool EnemyManager::Shoot(sf::RectangleShape& rect) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        if ( ((Enemy*)entityList[i])->GetState() != EnemyState::Dead ) {
            if ( ((Enemy*)entityList[i])->CheckCollisionCentered(rect, 1.0f) ) {
                ((Enemy*)entityList[i])->Die();
                return true;
            }
        }
    }

    return false;
}

/*
 * Gets vector list of dead enemies
 *
 * Returns:
 *      vector list pointer of enemy pointer containing dead enemies.
 */
std::vector<Enemy*>* EnemyManager::GetDead() {
    int i;
    std::vector<Enemy*>* dead = new std::vector<Enemy*>();

    for (i = entityList.size() - 1; i >= 0; i--) {
        if ( ((Enemy*)entityList[i])->GetState() == EnemyState::Dead ) {
            dead->push_back((Enemy*)entityList[i]);
        }
    }

    return dead;
}

/*
 * Destructs and deletes all dead enemies in the collection.
 */
void EnemyManager::DeleteDead() {
    int i;
    for (i = entityList.size() - 1; i >= 0; i--) {
        if ( ((Enemy*)entityList[i])->GetState() == EnemyState::Dead ) {
            delete entityList[i];
            entityList.erase(entityList.begin() + i);
        }
    }
}

/*
 * Calls enemy specific Update on enemies in collection.
 *
 * Parameters:
 *      deltaTime - determines speed restrictions and animation frames.
 *      playerPos - point where the player is.
 */
void EnemyManager::Update(float* deltaTime, sf::Vector2f playerPos) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        ((Enemy*)entityList[i])->Update(deltaTime, playerPos);
    }
}

/*
 * Checks collision on Entity with each enemy in collection
 * Filters based on enemy type.
 *
 * Parameters:
 *      ent - reference to an entity to check collision against
 *      push - resistance to collision
 *
 * Returns:
 *      bool true if a collision occurred else false
 */
bool EnemyManager::CheckCollisionPlayer(Entity& ent, float push) {
    int i;
    bool collided = false;

    for (i = 0; i < entityList.size(); i++) {

        collided = entityList[i]->CheckCollisionCentered(ent, push);

        if ( ((Enemy*)entityList[i])->GetType() == EnemyType::Evil || ((Enemy*)entityList[i])->GetType() == EnemyType::Mecha ) {
            if (collided) return collided;
        }

    }

    return collided;
}

