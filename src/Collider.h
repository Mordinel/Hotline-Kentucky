#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "TileType.h"

#define CHECK_DISTANCE 4
#define TILE_SIZE 32.0f

class Collider {
public:
    Collider(sf::RectangleShape& boundary, std::vector<std::vector<TileType>>* tileMap);
    ~Collider();

    void Move(float dx, float dy) { boundary.move(dx, dy); }
    virtual bool CheckCollision(Collider& other, float push);
    virtual bool CheckCollision(sf::RectangleShape& rect, float push);
    virtual bool CheckCollisionCentered(Collider& other, float push);
    virtual bool CheckCollisionCentered(sf::RectangleShape& rect, float push);

    sf::Vector2f GetColliderPosition() { return boundary.getPosition(); }
    sf::Vector2f GetHalfSize() { return boundary.getSize() / 2.0f; }

protected:

    sf::RectangleShape& boundary;
    std::vector<std::vector<TileType>>* tileMap;

    void checkCollisionsNearBody();
    void checkTilemapCollision(sf::Vector2f* movement);
    virtual bool checkCollision(sf::RectangleShape& rect, sf::Vector2f& thisPosition, sf::Vector2f& thisHalfSize, float push);
    virtual bool checkCollision(Collider& other, sf::Vector2f& thisPosition, sf::Vector2f& thisHalfSize, float push);
};

#endif
