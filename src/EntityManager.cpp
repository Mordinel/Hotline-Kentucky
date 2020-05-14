/******************************************************************************
 * Filename: EntityManager.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 12/05/2020
 * Description: Manages collections of entities
 *****************************************************************************/

#include "EntityManager.h"

/*
 * Entitymanager constructor
 */
EntityManager::EntityManager() {

}

/*
 * EntityManager destructor
 *
 * Clears the collection of entities
 */
EntityManager::~EntityManager() {
    DeleteAll();
}

/*
 * Appends an entity to the collection of entity.
 *
 * Parameters:
 *      entity pointer - a pointer to the entity to be stored in the collection
 */
void EntityManager::Append(Entity* entity) {
    entityList.push_back(entity);
}

/*
 * Deletes a specific entity from the collection
 *
 * Parameters:
 *      entity pointer - a pointer to the entity to be deleted from the collection
 */
void EntityManager::Delete(Entity* entity) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        if (entityList[i] == entity) {
            entityList.erase(entityList.begin() + i);
            return;
        }
    }
}

/*
 * Calls the Update() function on each entity in the collection.
 *
 * Parameters:
 *      deltaTime - passed to the Update() function.
 */
void EntityManager::Update(float* deltaTime) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        entityList[i]->Update(deltaTime);
    }
}

/*
 * Calls The Draw() function on each entity in the collection.
 *
 * Parameters:
 *      window - passed to the Draw() function.
 */
void EntityManager::Draw(sf::RenderWindow* window) {
    int i;
    for (i = 0; i < entityList.size(); i++) {
        entityList[i]->Draw(window);
    }
}

/*
 * Destroys and deletes all entities from the entity collection.
 */
void EntityManager::DeleteAll() {
    int i;
    // destroy each entity
    for (i = 0; i < entityList.size(); i++) {
        delete entityList[i];
    }

    // clear the pointers
    entityList.clear();
}

/*
 * Checks collision of ent with all entities in the collection.
 *
 * Parameters:
 *      ent - a reference to the entity to be checked for collision.
 *      push - the amount the entity will resist collision.
 */
void EntityManager::CheckCollision(Entity& ent, float push) {
    int i;    
    for (i = 0; i < entityList.size(); i++) {
        entityList[i]->CheckCollisionCentered(ent, push);
    }
}

/*
 * Checks collisions with each other entity in the collection.
 */
void EntityManager::CollideWithEntities() {
    int i;
    int j;
    for (i = 0; i < entityList.size(); i++) {
        for (j = 0; j < entityList.size(); j++) {
            if (i == j) continue;

            Entity* tmpEnt = entityList[j];
            entityList[i]->CheckCollisionCentered(*tmpEnt, PUSH_BACK_VALUE);
        }
    }
}

