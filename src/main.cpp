// main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Player.h"
#include "Dungeon.h"
#include "Room.h"
#include "TileType.h"
#include "TileMap.h"

#define ZOOM_INCREMENTS 0.2f
#define ZOOM_MIN 0.6f
#define ZOOM_MAX 4.0f
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

    //create render window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Hello world", sf::Style::None/* | sf::Style::Fullscreen*/);

    sf::Vector2f viewSize(window.getSize().x, window.getSize().y);
    sf::View view(sf::Vector2f(0.0f, 0.0f), viewSize);
    
    std::srand(random_seed);

    Dungeon d;
    std::vector<Room*> rooms = d.GetRooms();

    sf::Vector2f spawnLocation = rooms[0]->GetCenter() * (float)tileSize;

    std::vector<std::vector<TileType>> map = d.GenMap();

    sf::Texture* playerTexture = new sf::Texture();
    if (!playerTexture->loadFromFile("../assets/sprites/chicken.png")) return 1;

    Player player(playerTexture, &window, sf::Vector2u(8, 8), 0.125f, 300.0f, &map);
    sf::Vector2f playerPos;
    player.SetPosition(&spawnLocation);

    sf::Texture tileTexture;
    tileTexture.loadFromFile("../assets/sprites/tiles.png");
    TileMap tm(map, tileSize, tileTexture);

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
            }
        }

        playerPos = player.GetPosition();
        tm.CastLight(playerPos.x, playerPos.y);

        window.clear(sf::Color(29, 32, 33));
        window.draw(tm);
        window.setView(view);

        player.Update(&deltaTime);
        player.Draw(&window);
        view.setSize(viewSize * viewZoom);

        view.setCenter(player.GetPosition());
        
        // display the window
        window.display();
    }
    
    return 0;
}

