
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SFML/Graphics.hpp>
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

    Entity* Next;
protected:
    sf::RectangleShape body;
    sf::RenderWindow* window;
    Animation animation;
    unsigned int row;
    float speed;
};

#endif
