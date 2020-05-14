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

#define TILE_SIZE 32.0f
#define CHICKEN_ANIMATION_SIZE 8
#define CHICKEN_ANIMATIONS 8
#define ANIMATION_SWITCH_TIME 0.125f
#define PLAYER_SPEED 200.0f
#define BACKGROUND_COLOR sf::Color(29, 32, 33)
#define ZOOM_INCREMENTS 0.2f
#define ZOOM_MIN 0.6f
#define ZOOM_MAX 5.0f
#define ZOOM_DEFAULT 1.0f
#define TEXT_SIZE 24
#define TEXT_LOCATION 10, 10
#define ITEM_SPAWN_CHANCE 4 // 1 in 4
#define ROOM_COIN_COUNT 5

class GameManager {
private:
    sf::RenderWindow* window;
    sf::View view;
    sf::Font font;
    sf::Text levelText;
    sf::Text scoreText;
    sf::Text powerupText;
    std::string levelString;
    std::string scoreString;
    std::string powerupString;
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

    void handleWindowEvents();
    void setViewZoom(int mouseDelta);
    void spawnItems();
    void spawnThings();

public:
    GameManager(sf::RenderWindow* startWindow, sf::View startView, sf::Texture* playerTex, sf::Font startFont);
    ~GameManager();
    void Init();
    void Update(float deltaTime);
    void Draw();
    
};

#endif
