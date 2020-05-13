#include "Gun.h"

Gun::Gun(std::vector<std::vector<TileType>>* tileMap, EnemyManager* enemyManager) {
    this->tileMap = tileMap;
    this->enemyManager= enemyManager;
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

void Gun::Fire(sf::Vector2f& from, sf::Vector2f& to, sf::RenderWindow* window) {
    bool enemyHit = false;
    isFiring = true;

    sf::Vector2f aimDir = to - from;
    sf::Vector2f aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

    sf::RectangleShape tracer(sf::Vector2f(4.0f, 4.0f));
    tracer.setPosition(from);
    tracer.setFillColor(sf::Color::Green);
    //tracer.setOrigin(tracer.getSize() / 2.0f);

    sf::Vector2f tracerPos = tracer.getPosition();

    while((*tileMap)[(int)tracer.getPosition().y / 32][(int)tracer.getPosition().x / 32] != TileType::Wall && !enemyHit) {
        window->draw(tracer);
        tracerPos += aimDirNorm;
        tracer.setPosition(tracerPos);
        enemyHit = enemyManager->Shoot(tracer);
    }

    SetLineCoordinates(tracerPos, from);
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
