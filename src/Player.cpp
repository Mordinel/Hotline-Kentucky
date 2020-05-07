#include <SFML/Graphics.hpp>

#include "Player.h"

// construct default player object
Player::Player(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap) : Entity(texture, window, imageCount, switchTime, speed), Collider(body) {
    row = 7;
    lastMovement.x = 0.0f;
    lastMovement.y = 0.0f;
    this->tileMap = tileMap;
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
    collisionCheck(movement);
}

void Player::collisionCheck(sf::Vector2f movement) {
    float halfWidth = boundary.getSize().x / 2.0f;
    float halfHeight = boundary.getSize().y / 2.0f;
    float tileSize = 32.0f;

    sf::Vector2f thisPosition = GetColliderPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    sf::RectangleShape topLeft;
    sf::RectangleShape topRight;
    sf::RectangleShape bottomLeft;
    sf::RectangleShape bottomRight;

    topLeft.setSize(sf::Vector2f(tileSize, tileSize));
    topRight.setSize(sf::Vector2f(tileSize, tileSize));
    bottomLeft.setSize(sf::Vector2f(tileSize, tileSize));
    bottomRight.setSize(sf::Vector2f(tileSize, tileSize));

    topLeft.setPosition((float)(int)(boundary.getPosition().x - halfWidth), (int)(boundary.getPosition().y - halfHeight));
    topRight.setPosition((float)(int)(boundary.getPosition().x + halfWidth), (int)(boundary.getPosition().y - halfHeight));
    bottomLeft.setPosition((float)(int)(boundary.getPosition().x - halfWidth), (int)(boundary.getPosition().y + halfHeight));
    bottomRight.setPosition((float)(int)(boundary.getPosition().x + halfWidth), (int)(boundary.getPosition().y + halfHeight));

    bool tl = (*tileMap)[(int)(topLeft.getPosition().y / tileSize)][(int)(topLeft.getPosition().x / tileSize)] == TileType::Wall;
    bool tr = (*tileMap)[(int)(topRight.getPosition().y / tileSize)][(int)(topRight.getPosition().x / tileSize)] == TileType::Wall;
    bool bl = (*tileMap)[(int)(bottomLeft.getPosition().y / tileSize)][(int)(bottomLeft.getPosition().x / tileSize)] == TileType::Wall;
    bool br = (*tileMap)[(int)(bottomRight.getPosition().y / tileSize)][(int)(bottomRight.getPosition().x / tileSize)] == TileType::Wall;

    if (tl && bl) {         // left
        boundary.setPosition((topLeft.getPosition().x + topLeft.getSize().x) - (float)((boundary.getSize().x / 2.0f) - 1.0f), boundary.getPosition().y);
    } else if (tl && tr) {  // top
        boundary.setPosition(boundary.getPosition().x, (topLeft.getPosition().y + topLeft.getSize().y) - (float)((boundary.getSize().y / 2.0f) - 1.0f));
    } else if (tr && br) {  // right
        boundary.setPosition(topRight.getPosition().x - boundary.getSize().x / 2.0f, boundary.getPosition().y);
    } else if (bl && br) {  // bottom
        boundary.setPosition(boundary.getPosition().x, bottomLeft.getPosition().y - boundary.getSize().y / 2.0f);
    } else if (tl) {        // top left
        boundary.setPosition(topLeft.getPosition().x + topLeft.getSize().x - (float)(boundary.getSize().x / 2.0f - 1.0f), (topLeft.getPosition().y + topLeft.getSize().y) - (float)((boundary.getSize().y / 2.0f) - 1.0f));
    } else if (tr) {        // top right
        boundary.setPosition(topRight.getPosition().x - boundary.getSize().x / 2.0f,  (topRight.getPosition().y + topRight.getSize().y) - (float)((boundary.getSize().y / 2.0f) - 1.0f));
    } else if (bl) {        // bottom left

    } else if (br) {        // bottom right

    }
}

