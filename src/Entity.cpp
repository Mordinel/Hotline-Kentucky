#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Animation.h"

// Entity definition
Entity::Entity(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed) : animation(texture, imageCount, switchTime) {
    this->speed = speed;
    this->window = window;
    Next = nullptr;
    row = 0;

    body.setSize(sf::Vector2f(100.0f, 100.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
    body.setTexture(texture);
}

Entity::~Entity() {

}

// update entity animation and movement
void Entity::Update(float* deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);

    animation.Update(row, deltaTime);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
}

// draw entity to window
void Entity::Draw(sf::RenderWindow* window) {
    window->draw(body);
}
