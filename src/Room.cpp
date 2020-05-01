#include <iostream>

#include "Room.h"

Room::Room(int x, int y, int width, int height) {
    this->X = x - width / 2;
    this->Y = y - height / 2;
    this->Width = width;
    this->Height = height;
    this->ConnectsTo = nullptr; // not connected to anything
}

sf::Vector2f Room::GetCenter() {
    sf::Vector2f center(X + Width / 2.0f, Y + Height / 2.0f);
    return center;
}

