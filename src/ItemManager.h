#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "EntityManager.h"
#include "Entity.h"
#include "Item.h"
#include "ItemType.h"

class ItemManager : public EntityManager {
    public:
        ItemManager();
        ~ItemManager();
        void Draw(sf::RenderWindow* window, const std::vector<std::vector<bool>>& fogOfWar);
        void DeleteConsumed();
        void Update(float* deltaTime);
        void PrintItems();
        ItemType CheckCollisionPlayer(Entity& ent);
};

#endif