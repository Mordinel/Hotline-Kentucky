/******************************************************************************
 * Filename: GameManager.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 12/05/2020
 * Description: Handles game flow, ties all classes together.
 *****************************************************************************/

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
#include "EnemyType.h"
#include "PlayerState.h"
#include "ItemManager.h"
#include "GameState.h"

#define TILE_SIZE 32.0f
#define CHICKEN_ANIMATION_SIZE 8
#define CHICKEN_ANIMATIONS 8
#define CHICKEN_DENOM 50
#define GOOD_MIN 2
#define GOOD_MAX 10
#define GOOD_FRAMESPEED 0.2f
#define GOOD_SPEED 1.4f
#define GOOD_POINTS 500;
#define MECHA_MIN 0
#define MECHA_MAX 2
#define MECHA_FRAMESPEED 0.3f
#define MECHA_SPEED 5.0f
#define MECHA_POINTS 150
#define EVIL_FRAMESPEED 0.2f
#define EVIL_SPEED 1.4f
#define EVIL_POINTS 50
#define ENEMY_FRAMES 8, 8
#define MAX_CHICKEN_PER_ROOM 40
#define ANIMATION_SWITCH_TIME 0.125f
#define PLAYER_SPEED 200.0f
#define PLAYER_ENEMY_PUSH 0.4f
#define BACKGROUND_COLOR sf::Color(29, 32, 33)
#define ZOOM_INCREMENTS 0.2f
#define ZOOM_MIN 0.6f
#define ZOOM_MAX 3.0f
#define ZOOM_DEFAULT 1.0f
#define TEXT_SIZE 24
#define TEXT_LOCATION 10, 10
#define ITEM_SPAWN_CHANCE 4 // 1 in 4
#define ITEM_FRAMESPEED 0.2f
#define COIN_FRAMES 4, 1
#define COIN_POINTS 100
#define ROOM_COIN_COUNT 5

class GameManager {
private:
    sf::RenderWindow* window;
    sf::View view;
    sf::Font font;
    sf::Text levelText;
    sf::Text scoreText;
    sf::Text powerupText;
    sf::Text lossText;
    std::string levelString;
    std::string scoreString;
    std::string powerupString;
    std::string lossString;
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
    sf::Texture* evilTexture;
    sf::Texture* mechaTexture;
    sf::Texture* goodTexture;
    ItemManager* itemManager;
    sf::Texture* coinTexture;
    sf::Texture* speedTexture;
    sf::Texture* visibilityTexture;
    Gun* gun;
    int score;
    GameState gameState;

    void handleWindowEvents();
    void setViewZoom(int mouseDelta);
    void spawnItems();
    void spawnEnemies();
    sf::Vector2f getRandomLocationInRoom(Room* room);

public:
    GameManager(sf::RenderWindow* startWindow, sf::View startView, sf::Texture* playerTex, sf::Font startFont);
    ~GameManager();
    void Init();
    void Update(float deltaTime);
    void Draw();
    
};

#endif
