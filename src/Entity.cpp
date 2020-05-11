#include <SFML/Graphics.hpp>

#include "Entity.h"

// Entity definition
Entity::Entity(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap) : animation(texture, imageCount, switchTime), Collider(body, tileMap) {
    this->speed = speed;
    this->window = window;
    Next = nullptr;
    row = 0;

    body.setSize(sf::Vector2f(32.0f, 32.0f));
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
    checkCollisionsNearBody();
}

// draw entity to window
void Entity::Draw(sf::RenderWindow* window) {
    window->draw(body);
}

void Entity::Draw(sf::RenderWindow* window, const std::vector<std::vector<bool>>& fogOfWar) {
    sf::Vector2i positionOnMap = (sf::Vector2i)GetPosition() / 32;

    if (fogOfWar[positionOnMap.y][positionOnMap.x]) {
        window->draw(body);
    }
}

void Entity::SetPosition(sf::Vector2f* position) {
    body.setPosition(*position);
}

