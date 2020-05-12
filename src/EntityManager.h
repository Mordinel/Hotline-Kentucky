#ifndef ENTMANAGER_H
#define ENTMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Entity.h"

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
};

#endif
