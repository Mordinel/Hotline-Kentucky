// main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Player.h"
#include "Dungeon.h"
#include "Room.h"
#include "TileType.h"
#include "TileMap.h"

const unsigned int random_seed = static_cast<unsigned int>(time(NULL));
const int tileSize = 32;

int main()
{
    int i;

    //create render window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Hello world", sf::Style::None/* | sf::Style::Fullscreen*/);

    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window.getSize().x, window.getSize().y));

    sf::Texture* playerTexture = new sf::Texture();
    if (!playerTexture->loadFromFile("../assets/sprites/chicken.png")) return 1;

    Player player(playerTexture, &window, sf::Vector2u(8, 8), 0.125f, 500.0f);
    
    std::srand(random_seed);

    Dungeon d;
    std::vector<Room*> rooms = d.GetRooms();

    sf::Vector2f spawnLocation = rooms[0]->GetCenter() * (float)tileSize;
    player.SetPosition(&spawnLocation);

    std::vector<std::vector<TileType>> map = d.GenMap();

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
            }
        
        }
 
        window.clear(sf::Color(100, 100, 100));
        window.setView(view);
        view.setCenter(player.GetPosition());

        window.draw(tm);

        player.Update(&deltaTime);
        player.Draw(&window);

        // display the window
        window.display();
    }
    
    return 0;
}
