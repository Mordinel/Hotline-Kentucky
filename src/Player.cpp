#include <SFML/Graphics.hpp>

#include "Player.h"

// construct default player object
Player::Player(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap) : Entity(texture, window, imageCount, switchTime, speed, tileMap) {
    row = 7;
    lastMovement.x = 0.0f;
    lastMovement.y = 0.0f;
    state = PlayerState::Normal;
}

// define Update override to use 
void Player::Update(float* deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);

    // set next movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= speed * *deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += speed * *deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= speed * *deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += speed * *deltaTime;
    }

    
    // set sprite sheet row depending on direction
    if (movement.x == 0.0f && movement.y == 0.0f) { // idle

        if (lastMovement.x < 0.0f) {
            row = 4;
        } else if (lastMovement.x > 0.0f) {
            row = 5;
        } else if (lastMovement.y < 0.0f) {
            row = 6;
        } else if (lastMovement.y > 0.0f) {
            row = 7;
        }
        
    } else if (movement.x < 0.0f) { // west
        row = 0;
    } else if (movement.x > 0.0f) { // east
        row = 1;
    } else if (movement.y < 0.0f) { // north
        row = 2;
    } else if (movement.y > 0.0f) { // south
        row = 3;
    }

    lastMovement.x = movement.x;
    lastMovement.y = movement.y;

    animation.Update(row, deltaTime);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
    checkCollisionsNearBody();
}

