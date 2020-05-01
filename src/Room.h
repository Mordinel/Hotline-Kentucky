#ifndef ROOM_H
#define ROOM_H

#include <SFML/Graphics.hpp>

class Room {
public:
    Room(int x, int y, int width, int height);
    sf::Vector2f GetCenter();

    int X;
    int Y;
    int Width;
    int Height;
    Room* ConnectsTo;
};

#endif
