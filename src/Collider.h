#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "TileType.h"

class Collider {
public:
    Collider(sf::RectangleShape& boundary, std::vector<std::vector<TileType>>* tileMap);
    ~Collider();

    void Move(float dx, float dy) { boundary.move(dx, dy); }
    virtual bool CheckCollision(Collider& other, float push);

    sf::Vector2f GetColliderPosition() { return boundary.getPosition(); }
    sf::Vector2f GetHalfSize() { return boundary.getSize() / 2.0f; }

protected:
    sf::RectangleShape& boundary;
    std::vector<std::vector<TileType>>* tileMap;

    void checkTilemapCollision(sf::Vector2f movement);
};

#endif
