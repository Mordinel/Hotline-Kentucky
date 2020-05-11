#include "Gun.h"

Gun::Gun(std::vector<std::vector<TileType>>* tileMap, EnemyList& enemyList) {
    this->tileMap = tileMap;
    this->enemyList = enemyList;
    sightLine.setPrimitiveType(sf::Lines);
    sightLine.resize(LINE_VERTEX_COUNT);
    isFiring = false;

    setColor(sf::Color::White);
    
    totalTime = 0;
    switchTime = FIRE_ANIMATION_LEN;
}

Gun::~Gun(){}

void Gun::SetLineCoordinates(sf::Vector2f playerPos, sf::Vector2f cursorPos) {
    sightLine[0].position = playerPos;
    sightLine[1].position = cursorPos;
}

void Gun::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (isFiring)
    {
        target.draw(sightLine, states);
    }
}

void Gun::Fire(sf::Vector2f& from, sf::Vector2f& to) {
    isFiring = true;

    float shootAngle;
    float x;
    float y;
    float n;

    float ox = from.x / 32.0f;
    float oy = from.y / 32.0f;

    float fromY = from.y;
    float fromX = from.x;
    float toY = to.y;
    float toX = to.x;

    float a = toX - fromX;
    float o = toY - fromY;

    // pray to god lol
    shootAngle = std::tan(o / a);

    x = std::cos(shootAngle); 
    y = std::sin(shootAngle);

    do {
        if ((int)oy > (*tileMap).size() || (int)ox > (*tileMap)[0].size()) {
            return;
        }

        if ((int)oy < 0 || (int)ox < 0) {
            return;
        }

        sf::RectangleShape tmpRect; 
        tmpRect.setSize(sf::Vector2f(1.0f, 1.0f));
        tmpRect.setPosition(sf::Vector2f(ox * 32.0f, oy * 32.0f));

        ox += x;
        oy += y;
    } while((*tileMap)[(int)oy][(int)ox] != TileType::Wall); // while tile not wall

    SetLineCoordinates(sightLine[0].position, sf::Vector2f(ox * 32.0f, oy * 32.0f));
}

void Gun::Update(float* deltaTime) {

    if (isFiring)
    {
        totalTime += *deltaTime;
    }

    if (totalTime >= switchTime) {
        totalTime = 0.0f;
        isFiring = false;
    }    
}

void Gun::setColor(sf::Color color) {
    sightLine[0].color = color;
    sightLine[1].color = color;
}
