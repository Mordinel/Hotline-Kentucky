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

void Gun::Fire(sf::Vector2f& from, sf::Vector2f& to, sf::RenderWindow* window) {
    isFiring = true;

    sf::Vector2f aimDir = to - from;
    sf::Vector2f aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

    sf::RectangleShape tracer(sf::Vector2f(16.0f, 16.0f));
    tracer.setPosition(from);
    tracer.setFillColor(sf::Color::Magenta);

    sf::Vector2f tracerPos = tracer.getPosition();

    while((*tileMap)[(int)tracer.getPosition().y / 32][(int)tracer.getPosition().x / 32] != TileType::Wall) {
        window->draw(tracer);
        tracerPos += aimDirNorm;
        tracer.setPosition(tracerPos);
        enemyList.Shoot(tracer);
    }

    /*float shootAngle;
    float x;
    float y;
    float n;

    float ox = from.x;
    float oy = from.y;

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
    std::cout << "X: " << x << " Y: " << y << std::endl; 
    do {
        if ((int)oy > toY || (int)ox > toX) {
            return;
        }

        if ((int)oy < 0 || (int)ox < 0) {
            return;
        }
        std::cout << "OX: " << ox << " OY: " << oy << std::endl; 

        sf::RectangleShape tmpRect; 
        tmpRect.setSize(sf::Vector2f(4.0f, 4.0f));
        tmpRect.setPosition(sf::Vector2f(ox, oy));
        tmpRect.setFillColor(sf::Color::Green);
        window->draw(tmpRect);

        
        enemyList.Shoot(tmpRect);

        ox += x;
        oy += y;
    } while((*tileMap)[(int)oy / 32][(int)ox / 32] != TileType::Wall); // while tile not wall*/

    SetLineCoordinates(to, from);
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
