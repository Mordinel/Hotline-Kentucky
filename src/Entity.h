/******************************************************************************
 * Filename: Entity.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 01/05/2020
 * Description: Implements movement, drawing and animation of all sprites, inherits collider.
 *****************************************************************************/

#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "math.h"
#include "Animation.h"
#include "Collider.h"

// define entity class
class Entity : public Collider {
public:
    Entity(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap);
    ~Entity();
    virtual void Update(float* deltaTime);
    virtual void Draw(sf::RenderWindow* window);
    virtual void Draw(sf::RenderWindow* window, const std::vector<std::vector<bool>>& fogOfWar);

    virtual sf::Vector2f GetPosition() { return body.getPosition(); }
    virtual void SetPosition(sf::Vector2f* position);
    virtual void SetPosition(sf::Vector2f position);
    virtual float GetDistanceBetween(sf::Vector2f location);

    Entity* Next;
protected:
    sf::RectangleShape body;
    sf::RenderWindow* window;
    Animation animation;
    unsigned int row;
    float speed;
};

#endif
