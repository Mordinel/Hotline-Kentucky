/******************************************************************************
 * Filename: Gun.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 09/05/2020
 * Description: Handles gun shooting and bullet collision with game entities.
 *****************************************************************************/

#include "Gun.h"

/*
 * Gun constructor
 *
 * Parameters:
 *      tileMap - a map of tiles used for collision
 *      enemyManager - the manager for enemies to check bullet collision against.
 */
Gun::Gun(std::vector<std::vector<TileType>>* tileMap, EnemyManager* enemyManager) {
    this->tileMap = tileMap;
    this->enemyManager= enemyManager;
    sightLine.setPrimitiveType(sf::Lines);
    sightLine.resize(LINE_VERTEX_COUNT);
    isFiring = false;

    setColor(sf::Color::White);
    
    totalTime = 0;
    switchTime = FIRE_ANIMATION_LEN;
}

/*
 * Gun destructor
 */
Gun::~Gun(){}

/*
 * Sets line coordinates
 *
 * Parameters:
 *      playerPos - position to draw the line from
 *      cursorPos - position to cast the line through
 */
void Gun::SetLineCoordinates(sf::Vector2f playerPos, sf::Vector2f cursorPos) {
    sightLine[0].position = playerPos;
    sightLine[1].position = cursorPos;
}

/*
 * Draws the gun's line if gun is firing.
 *
 * Parameters:
 *      target - target to be drawn to
 *      states - render states (sfml lib thing)
 */
void Gun::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (isFiring)
    {
        target.draw(sightLine, states);
    }
}

/*
 * Fires the gun
 *
 * Parameters:
 *      from - the point of origin for the bullet line.
 *      to - the point to determine the vector of the bullet line.
 *      window - for bullet debug rendering (not seen in gameplay)
 */
void Gun::Fire(sf::Vector2f& from, sf::Vector2f& to, sf::RenderWindow* window) {
    bool enemyHit = false;
    isFiring = true;

    sf::Vector2f aimDir = to - from;
    sf::Vector2f aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

    sf::RectangleShape tracer(sf::Vector2f(4.0f, 4.0f));
    tracer.setPosition(from);

    sf::Vector2f tracerPos = tracer.getPosition();

    // cast the bullet until it hits a wall or enemy
    while((*tileMap)[(int)tracer.getPosition().y / 32][(int)tracer.getPosition().x / 32] != TileType::Wall && !enemyHit) {
        tracerPos += aimDirNorm;
        tracer.setPosition(tracerPos);
        enemyHit = enemyManager->Shoot(tracer);
    }

    // set the destination coordinate
    SetLineCoordinates(tracerPos, from);
}

/*
 * update the gun
 *
 * Parameters:
 *      deltaTime - used to display the bullet line for a certain amount of time.
 */
void Gun::Update(float* deltaTime) {

    if (isFiring)
    {
        totalTime += *deltaTime;
    }

    if (totalTime >= switchTime) {
        totalTime = 0.0f;
        isFiring = false;
    }
}

/*
 * sets the colour of the bullet line.
 *
 * Parameters:
 *      color - the colour to set the bullet lines.
 */
void Gun::setColor(sf::Color color) {
    sightLine[0].color = color;
    sightLine[1].color = color;
}
