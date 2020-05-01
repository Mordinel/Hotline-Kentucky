// main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Dungeon.h"
#include "Room.h"

const unsigned int random_seed = static_cast<unsigned int>(time(NULL));
const int tileSize = 4;

int main()
{
    int i;
    //create render window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML Hello world", sf::Style::Close | sf::Style::Titlebar);

    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window.getSize().x, window.getSize().y));

    sf::Texture* playerTexture = new sf::Texture();;
    if (!playerTexture->loadFromFile("../assets/sprites/chicken.png")) return 1;

    Player player(playerTexture, &window, sf::Vector2u(8, 8), 0.125f, 500.0f);
    
    std::srand(random_seed);

    Dungeon d;
    std::vector<Room*> rooms = d.GetRooms();
   
    for (i = 0; i < rooms.size(); i++) {
        printf("Room %d: X:%d Y:%d W:%d H:%d\n",i, rooms[i]->X, rooms[i]->Y, rooms[i]->Width, rooms[i]->Height); 
    }

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

        for (i = 0; i < rooms.size(); i++) {

            sf::RectangleShape rect(sf::Vector2f((float)rooms[i]->Width * tileSize, (float)rooms[i]->Height * tileSize));
            rect.setPosition(rooms[i]->X * tileSize, rooms[i]->Y * tileSize);

            rect.setOutlineColor(sf::Color(255, 255, 255));
            rect.setFillColor(sf::Color(255, 255, 255, 0));
            rect.setOutlineThickness(1);

            window.draw(rect);
        }

        player.Update(&deltaTime);
        player.Draw(&window);

        // display the window
        window.display();
    }
    
    return 0;
}
