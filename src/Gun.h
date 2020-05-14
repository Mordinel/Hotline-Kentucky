/******************************************************************************
 * Filename: Gun.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 09/05/2020
 * Description: Handles gun shooting and collision with game entities.
 *****************************************************************************/

#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "EnemyManager.h"
#include "TileType.h"

#define LINE_VERTEX_COUNT 2
#define FIRE_ANIMATION_LEN 0.1f
#define TRACER_SIZE 0.0f, 0.0f
#define TILE_FACTOR 32

class Gun : public sf::Drawable {
private:
    sf::VertexArray sightLine;
    float totalTime;
    float switchTime;
    std::vector<std::vector<TileType>>* tileMap;
    EnemyManager* enemyManager;
    bool isFiring;

    void setColor(sf::Color color);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Gun(std::vector<std::vector<TileType>>* tileMap, EnemyManager* enemyManager);
    ~Gun();
    void SetLineCoordinates(sf::Vector2f playerPos, sf::Vector2f cursorPos);
    void Fire(sf::Vector2f& from, sf::Vector2f& to, sf::RenderWindow* window);
    void Update(float* deltaTime);
};

#endif
