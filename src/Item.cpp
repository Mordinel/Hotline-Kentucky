#include "Item.h"

Item::Item(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMapm, ItemType startItemType) : Entity(texture, window, imageCount, switchTime, speed, tileMap) {
    itemType = startItemType;
}

ItemType Item::GetItemType() {
    return itemType;
}

void Item::SetItemType(ItemType newType) {
    itemType = newType;
}