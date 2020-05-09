#include "Gun.h"

Gun::Gun() {
    sightLine.setPrimitiveType(sf::Lines);
    sightLine.resize(LINE_VERTEX_COUNT);

    setColor(sf::Color::Red);
    
    totalTime = 0;
    switchTime = FIRE_ANIMATION_LEN;
}

Gun::~Gun(){}

void Gun::SetLineCoordinates(sf::Vector2f playerPos, sf::Vector2f cursorPos) {
    sightLine[0].position = playerPos;
    sightLine[1].position = cursorPos;
}

void Gun::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sightLine, states);
}

void Gun::Fire() {
    setColor(sf::Color::Red);
}

void Gun::Update(float* deltaTime) {

    if (sightLine[0].color == sf::Color::Red)
    {
        totalTime += *deltaTime;
    }

    if (totalTime >= switchTime) {
        totalTime = 0.0f;
        setColor(sf::Color::White);
    }    
}

void Gun::setColor(sf::Color color) {
    sightLine[0].color = color;
    sightLine[1].color = color;
}