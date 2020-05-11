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
    int i;
    float viewZoom = ZOOM_DEFAULT;

    int levelCount = 1;
    sf::Font font;
    font.loadFromFile("../assets/font.ttf");
    std::string levelString = "Level: " + std::to_string(levelCount);
    sf::Text levelText;
    levelText.setFont(font);
    levelText.setString(levelString);
    levelText.setCharacterSize(16);
    levelText.setFillColor(sf::Color::White);

    //create render window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Roguelike", sf::Style::Titlebar | sf::Style::Close /*sf::Style::None/* | sf::Style::Fullscreen*/);
    window.setVerticalSyncEnabled(true);

    sf::Vector2f viewSize(window.getSize().x, window.getSize().y);
    sf::View view(sf::Vector2f(0.0f, 0.0f), viewSize);
    
    std::srand(random_seed);

    Dungeon d;
    std::vector<Room*> rooms = d.GetRooms();

    sf::Vector2f spawnLocation = rooms[0]->GetCenter() * (float)tileSize;

    // Dungeon Exit Code
    sf::RectangleShape exitRect(sf::Vector2f(tileSize, tileSize));
    sf::Vector2f exitLocation = d.GetExitLocation() * (float)tileSize;
    exitRect.setPosition(exitLocation);

    std::vector<std::vector<TileType>> map = d.GenMap();

    sf::Texture* playerTexture = new sf::Texture();
    if (!playerTexture->loadFromFile("../assets/sprites/chicken.png")) return 1;

    Player player(playerTexture, &window, sf::Vector2u(8, 8), 0.125f, 300.0f, &map);
    sf::Vector2f playerPos;
    player.SetPosition(&spawnLocation);

    sf::Texture tileTexture;
    tileTexture.loadFromFile("../assets/sprites/tiles.png");
    TileMap tm(map, tileSize, tileTexture);

    Gun gun;
    sf::RectangleShape shp(sf::Vector2f(1.0f, 1.0f));
    Collider c(shp, &map);

    sf::Texture* enemyTexture = new sf::Texture();
    if (!enemyTexture->loadFromFile("../assets/sprites/evil-chicken.png")) return 1;
    Enemy enemy(enemyTexture, &window, sf::Vector2u(8, 8), 0.125f, 300.0f, &map);
    sf::Vector2f enemySpawn = rooms[1]->GetCenter() * (float)tileSize;
    enemy.SetPosition(&enemySpawn);


    float deltaTime = 0.0f;
    sf::Clock* clock = new sf::Clock();
    // while window is open
    while (window.isOpen()) {
        deltaTime = clock->restart().asSeconds();

        sf::Event evnt;

        // poll the window for events
        while (window.pollEvent(evnt)) {

            // switch on the event type
            switch(evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseWheelMoved:
                    setViewZoom(&viewZoom, evnt.mouseWheel.delta);
                    break;
                case sf::Event::MouseButtonPressed:
                    gun.Fire();
                    break;
            }
        }

        playerPos = player.GetPosition();
        tm.CastLight(playerPos.x, playerPos.y);

        window.clear(sf::Color(29, 32, 33));
        window.draw(tm);

        player.Update(&deltaTime);
        sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
        sf::Vector2f relativeCursorPos = window.mapPixelToCoords(cursorPos);
        gun.SetLineCoordinates(player.GetPosition(), relativeCursorPos);
        gun.Update(&deltaTime);
        enemy.Update(&deltaTime);
        player.CheckCollision(enemy, 0.1f);

        
        std::vector<std::vector<bool>> fogOfWar = tm.LitMaskToFogOfWar();
        
        window.draw(gun);
        enemy.Draw(&window, fogOfWar);
        player.Draw(&window);
        view.setSize(viewSize * viewZoom);

        view.setCenter(player.GetPosition());
        window.setView(view);

        levelText.setPosition(window.mapPixelToCoords(sf::Vector2i(20, 20)));
        window.draw(levelText);
        
        // display the window
        window.display();

        // Did the player reach the exit?
        if (player.CheckCollision(exitRect, 0.0f))
        {
            d.NextDungeon();
            map = d.GenMap();
            rooms = d.GetRooms();
            tm.SetTiles(map);

            spawnLocation = rooms[0]->GetCenter() * (float)tileSize;
            player.SetPosition(&spawnLocation);

            exitLocation = d.GetExitLocation() * (float)tileSize;
            exitRect.setPosition(exitLocation);

            levelCount++;
            levelString = "Level: " + std::to_string(levelCount);
            levelText.setString(levelString);
        }
    }
    
    return 0;
}

