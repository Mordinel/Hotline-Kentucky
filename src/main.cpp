// main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Player.h"
#include "Dungeon.h"
#include "Room.h"
#include "TileType.h"
#include "TileMap.h"
#include "Gun.h"
#include "Enemy.h"
#include "EntityManager.h"
#include "EnemyManager.h"
#include "Item.h"
#include "ItemType.h"
#include "GameManager.h"

#define ZOOM_INCREMENTS 0.2f
#define ZOOM_MIN 0.6f
#define ZOOM_MAX 100.0f
#define ZOOM_DEFAULT 1.0f

const unsigned int random_seed = static_cast<unsigned int>(time(NULL));
const int tileSize = 32;

void setViewZoom(float* viewZoom, int mouseDelta) {
    if (mouseDelta < 0) {
        *viewZoom += ZOOM_INCREMENTS;
    } else if (mouseDelta > 0) {
        *viewZoom -= ZOOM_INCREMENTS;
    }

    if (*viewZoom < ZOOM_MIN) {
        *viewZoom = ZOOM_MIN;
    } else if (*viewZoom > ZOOM_MAX) {
        *viewZoom = ZOOM_MAX;
    }
}

int main()
{
    // Set up
    std::srand(random_seed);

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Roguelike", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::Vector2f viewSize(window.getSize().x, window.getSize().y);
    sf::View view(sf::Vector2f(0.0f, 0.0f), viewSize);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../assets/sprites/chicken.png")) return 1;

    sf::Font font;
    if(!font.loadFromFile("../assets/font.ttf")) return 1;

    GameManager gm(&window, view, &playerTexture, font);

    float deltaTime = 0.0f;
    sf::Clock* clock = new sf::Clock();

    // Game Loop
    while (window.isOpen()) {
        deltaTime = clock->restart().asSeconds();
        gm.Update(deltaTime);
        gm.Draw();
    }

    return 0;
}

