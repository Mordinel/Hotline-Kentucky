/******************************************************************************
 * Filename: Item.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 14/05/2020
 * Description: Class representing an item
 *****************************************************************************/

#include "Item.h"

/*
 * Player Constructor
 *
 * Parameters:
 *      texture - the texture for the player
 *      window - the window the player will be drawn to
 *      imageCount - the image count of the texture
 *      switchTime - the speed of the animation transitions
 *      speed - how fast the entity will move
 *      tileMap - a matrix of tileTypes
 *      itemType- the type of item
 */
Item::Item(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMapm, ItemType startItemType) : Entity(texture, window, imageCount, switchTime, speed, tileMap) {
    itemType = startItemType;
    body.setSize(sf::Vector2f(ITEM_SIZE, ITEM_SIZE));
    consumed = false;
}

/*
 * Get the item type
 * 
 * Returns:
 *      The item type
 */
ItemType Item::GetItemType() {
    return itemType;
}

/*
 * Set the item type
 */
void Item::SetItemType(ItemType newType) {
    itemType = newType;
}

/*
 * Update the item
 */
void Item::Update(float* deltaTime) {
    animation.Update(row, deltaTime);
    body.setTextureRect(animation.uvRect);
}

/*
 * Get the boolean value of whether the item has been consumed by the player or not.
 */ 
bool Item::GetConsumed() {
    return consumed;
}

/*
 * Set the boolean value of whether the item has been consumed by the player or not.
 */ 
void Item::SetConsumed(bool isConsumed) {
    consumed = isConsumed;
}