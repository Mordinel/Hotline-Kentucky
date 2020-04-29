// main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Dungeon.h"
#include "Room.h"

const unsigned long random_seed = 20;

int main()
{
    // create render window
    //sf::RenderWindow window(sf::VideoMode(1024, 512), "SFML Hello world", sf::Style::Close | sf::Style::Titlebar);
    
    std::srand(random_seed);

    // while window is open
   // while (window.isOpen()) {

   //     sf::Event evnt;
   //     // poll the window for events
   //     while (window.pollEvent(evnt)) {

   //         // switch on the event type
   //         switch(evnt.type) {
   //             case sf::Event::Closed:
   //                 window.close();
   //                 break;
   //         }
   //     
   //     }
   //     // display the window
   //     window.display();
   // }
    
    //delete window;

    Dungeon d;
    std::vector<Room*> rooms = d.GetRooms();
    
    for (int i = 0; i < rooms.size(); i++)
    {
        printf("X:%d Y:%d W:%d H:%d\n", rooms[i]->X, rooms[i]->Y, rooms[i]->Width, rooms[i]->Height);
    }


    return 0;
}