// main.cpp
#include <SFML/Graphics.hpp>

#include "GameManager.h"

const unsigned int random_seed = static_cast<unsigned int>(time(NULL));

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

