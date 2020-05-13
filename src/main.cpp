/******************************************************************************
 * Filename: main.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 29/04/2020
 * Description: Entry point of the program. Creates and runs the game loop.
 *****************************************************************************/

#include <SFML/Graphics.hpp>
#include "GameManager.h"

const unsigned int random_seed = static_cast<unsigned int>(time(NULL));

int main()
{
    // Set up
    std::srand(random_seed);

    // Creates the game window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Hotline Kentucky", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    // Creates the viewport of the game world
    sf::Vector2f viewSize(window.getSize().x, window.getSize().y);
    sf::View view(sf::Vector2f(0.0f, 0.0f), viewSize);

    // Loads the player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../assets/sprites/chicken.png")) return 1;

    // Loads the font used for text rendering
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

