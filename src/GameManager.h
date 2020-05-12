#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Dungeon.h"
#include "Room.h"
#include "TileType.h"
#include "TileMap.h"
#include "Entity.h"
#include "Player.h"
#include "Gun.h"
#include "Enemy.h"
#include "Item.h"
#include "ItemType.h"

#define TILE_SIZE 32.0f
#define CHICKEN_ANIMATION_SIZE 8
#define CHICKEN_ANIMATIONS 8
#define ANIMATION_SWITCH_TIME 0.2f
#define PLAYER_SPEED 300.0f
#define BACKGROUND_COLOR sf::Color(29, 32, 33)
#define ZOOM_INCREMENTS 0.2f
#define ZOOM_MIN 0.6f
#define ZOOM_MAX 100.0f
#define ZOOM_DEFAULT 1.0f
#define TEXT_SIZE 14
#define TEXT_LOCATION 10, 10

class GameManager {
private:
    sf::RenderWindow* window;
    sf::View view;
    sf::Font font;
    sf::Text levelText;
    std::string levelString;
    float viewZoom;
    Dungeon dungeon;
    int levelCount;
    std::vector<std::vector<TileType>> map;
    std::vector<Room*> rooms;
    sf::RectangleShape exitRect;
    TileMap* tileMap;
    Player* player;
    std::vector<std::vector<bool>> fogOfWar;
    EnemyManager* enemyManager;
    sf::Texture* enemyTexture;
    Gun* gun;

    void handleWindowEvents();
    void setViewZoom(int mouseDelta);

public:
    GameManager(sf::RenderWindow* startWindow, sf::View startView, sf::Texture* playerTex, sf::Font startFont);
    ~GameManager();
    void Init();
    void Update(float deltaTime);
    void Draw();
};

#endif
