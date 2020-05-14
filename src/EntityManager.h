/******************************************************************************
 * Filename: EntityManager.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 12/05/2020
 * Description: Manages collections of entity.
 *****************************************************************************/

#ifndef ENTMANAGER_H
#define ENTMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Entity.h"

#define HALF_OFFSET 0.5f

class EntityManager {
protected:
    std::vector<Entity*> entityList;

public:
    EntityManager();
    ~EntityManager();

    virtual void Append(Entity* entity);
    virtual void Delete(Entity* entity);
    virtual void Update(float* deltaTime);
    virtual void Draw(sf::RenderWindow* window);
    virtual void DeleteAll();
    virtual void CheckCollision(Entity& ent, float push);
    virtual void CollideWithEntities();
};

#endif
