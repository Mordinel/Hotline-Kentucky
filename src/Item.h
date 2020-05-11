#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "ItemType.h"

class Item : public Entity {
private:
    ItemType itemType;

public:
    Item(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap, ItemType startItemType);
    ItemType GetItemType();
    void SetItemType(ItemType newType);
    void Update(float* deltaTime) override;
};

#endif