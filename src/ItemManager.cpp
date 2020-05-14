/******************************************************************************
 * Filename: ItemManager.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 14/05/2020
 * Description: Manages a collection of items
 *****************************************************************************/

#include "ItemManager.h"

/*
 * ItemManagers default constructor and destructor
 */
ItemManager::ItemManager() : EntityManager() {}
ItemManager::~ItemManager() {}

/*
 * Draws all the items in the collection
 *
 * Parameters:
 *      window - the window to draw the items on to
 *      fogOfWar - the fog of war matrix used to determine if an item should be drawn     
 */
void ItemManager::Draw(sf::RenderWindow* window, const std::vector<std::vector<bool>>& fogOfWar) {
    for (int i = 0; i < entityList.size(); i++) {
        entityList[i]->Draw(window, fogOfWar);
    }
}

/*
 * Deletes all items that have been consumed by the player
 */
void ItemManager::DeleteConsumed() {
    for (int i = 0; i < entityList.size(); i++) {
        if (((Item*)entityList[i])->GetConsumed() == true) {
            delete entityList[i];
            entityList.erase(entityList.begin() + i);
        }
    }
}

/*
 * Updates all the items in the collection
 *  
 * Parameters:
 *      deltaTime - the amount of time passed since the last game loop
 */
void ItemManager::Update(float* deltaTime) {
    for (int i = 0; i < entityList.size(); i++) {
        entityList[i]->Update(deltaTime);
    }
}

/*
 * Checks if the player is colliding with an item.
 * If they are the item will be set as consumed and returned.
 *  
 * Parameters:
 *      ent - an entity most likely the player
 * 
 * Returns:
 *      An ItemType. Set to None if the player has not collided with an item.
 */
ItemType ItemManager::CheckCollisionPlayer(Entity& ent) {
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i]->CheckCollisionCentered(ent, 0.0f)) {
            ((Item*)entityList[i])->SetConsumed(true);
            return ((Item*)entityList[i])->GetItemType();
        }
    }

    return ItemType::None;
}


/*
 * Prints out all the item types for debug purposes
 */
void ItemManager::PrintItems() {
    for (int i = 0; i < entityList.size(); i++) {
        switch(((Item*)entityList[i])->GetItemType()) {
            case ItemType::Coin:
                std::cout << "Coin" << std::endl;
                break;
            case ItemType::Speed:
                std::cout << "Speed" << std::endl;
                break;
            case ItemType::Vision:
                std::cout << "Vison" << std::endl;
        }
    }
}