// main.cpp
#include <SFML/Graphics.hpp>

int main()
{
    // create render window
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1024, 512), "SFML Hello world", sf::Style::Close | sf::Style::Titlebar);

    // while window is open
    while (window->isOpen()) {

        sf::Event evnt;
        // poll the window for events
        while (window->pollEvent(evnt)) {

            // switch on the event type
            switch(evnt.type) {
                case sf::Event::Closed:
                    window->close();
                    break;
            }

        }

        // display the window
        window->display();
    }

    return 0;
}


