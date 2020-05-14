/******************************************************************************
 * Filename: Entity.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 01/05/2020
 * Description: Implements movement, animation, of all entities, inherits collider.
 *****************************************************************************/

#include <SFML/Graphics.hpp>

#include "Entity.h"

/*
 * Entity Constructor
 *
 * Parameters:
 *      texture - the texture to be rendered
 *      window - the window to be drawn to
 *      imagecount - the image dimensions of the texturemap
 *      switchtime - the speed at which the animation frames switch
 *      speed - the speed the entity moves at
 *      tileMap - a matrix of TileType for collision
 */
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

/*
 * Entity destructor
 */
Entity::~Entity() {

}

/*
 * Entity updater
 * updates movement, updates animation.
 *
 * parameters:
 *      deltaTime - determines what animation frame is to be rendered.
 */
void Entity::Update(float* deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);

    animation.Update(row, deltaTime);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
    checkCollisionsNearBody();
}

/*
 * tells the window to draw the entity.
 *
 * Parameters:
 *      window - the window to be drawn to
 */
void Entity::Draw(sf::RenderWindow* window) {
    window->draw(body);
}

/*
 * tells the window to draw the entity taking into account the fog of war
 *
 * Parameters:
 *      window - the window to be drawn to
 *      fogOfWar - the fog of war map to determine visibility
 */
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

/*
 * Sets the entity's body position
 *
 * Parameters:
 *      position - the position vector pointer to set the entity position to
 */
void Entity::SetPosition(sf::Vector2f* position) {
    body.setPosition(*position);
}

/*
 * Sets the entity's body position
 *
 * Parameters:
 *      position - the position vector to set the entity position to
 */
void Entity::SetPosition(sf::Vector2f position) {
    body.setPosition(position);
}

/*
 * Gets the euclidean distance between this entity and a position
 *
 * Parameter:
 *      location - the point to get the distance to
 *
 * Returns:
 *      float distance to the location
 */
float Entity::GetDistanceBetween(sf::Vector2f location) {
    sf::Vector2f entityPos = body.getPosition();

    float x1 = entityPos.x;
    float x2 = location.x;
    float y1 = entityPos.y;
    float y2 = location.y;

    float distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));

    return distance;
}

