/******************************************************************************
 * Filename: ItemManager.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 11/05/2020
 * Description: Manages a collection of items
 *****************************************************************************/

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