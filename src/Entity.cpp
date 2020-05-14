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

    // Tests edge case where entity might be in the "real" void causing a crash.
    if (positionOnMap.x > 0 && positionOnMap.x < fogOfWar[0].size() &&  positionOnMap.y > 0 && positionOnMap.y < fogOfWar.size()) {
        // Only draw if in a visible portion of fog of war
        if (fogOfWar[positionOnMap.y][positionOnMap.x]) {
            window->draw(body);
        }
    }
    
}

void Entity::SetPosition(sf::Vector2f* position) {
    body.setPosition(*position);
}

void Entity::SetPosition(sf::Vector2f position) {
    body.setPosition(position);
}

float Entity::GetDistanceBetween(sf::Vector2f location) {
    sf::Vector2f entityPos = body.getPosition();

    float x1 = entityPos.x;
    float x2 = location.x;
    float y1 = entityPos.y;
    float y2 = location.y;

    float distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));

    return distance;
}

