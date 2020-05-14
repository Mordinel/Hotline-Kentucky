/******************************************************************************
 * Filename: Item.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 14/05/2020
 * Description: Class representing an item
 *****************************************************************************/

#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "ItemType.h"

#define ITEM_SIZE 16.0f

class Item : public Entity {
private:
    ItemType itemType;
    bool consumed;

public:
    Item(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap, ItemType startItemType);
    ItemType GetItemType();
    void SetItemType(ItemType newType);
    void Update(float* deltaTime) override;
    bool GetConsumed();
    void SetConsumed(bool isConsumed);
};

#endif