
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "Animation.h"

// define entity class
class Entity {
public:
    Entity(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed);
    ~Entity();
    virtual void Update(float* deltaTime);
    virtual void Draw(sf::RenderWindow* window);

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
