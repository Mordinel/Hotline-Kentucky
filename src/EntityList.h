#ifndef ENTLIST_H
#define ENTLIST_H

#include <SFML/Graphics.hpp>

#include "Entity.h"

// define linkedlist of entities
class EntityList {
protected:
    Entity* head;
    Entity* tail;
    
public:
    EntityList();
    ~EntityList();

    virtual void Append(Entity* entity);
    virtual void Delete(Entity* entity);
    virtual void Update(float* deltaTime);
    virtual void Draw(sf::RenderWindow* window);
    virtual void DeleteAll();
    virtual int EntityCount();

    virtual Entity* GetHead() { return head; }
    virtual Entity* GetTail() { return tail; }
};

#endif
