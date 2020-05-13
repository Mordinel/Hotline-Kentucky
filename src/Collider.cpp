#include "Collider.h"

Collider::Collider(sf::RectangleShape& boundary, std::vector<std::vector<TileType>>* tileMap) : boundary(boundary) {
    this->tileMap = tileMap;
}

Collider::~Collider() {

}

void Collider::checkCollisionsNearBody() {
    int y;
    int x;

    // get check distance offset
    int minY = (int)((GetColliderPosition().y / TILE_SIZE) - CHECK_DISTANCE);
    int minX = (int)((GetColliderPosition().x / TILE_SIZE) - CHECK_DISTANCE);
    int maxY = (int)((GetColliderPosition().y / TILE_SIZE) + CHECK_DISTANCE);
    int maxX = (int)((GetColliderPosition().x / TILE_SIZE) + CHECK_DISTANCE);

    // check for dungeon bounds
    minY = (minY < 0) ? 0 : minY;
    minX = (minX < 0) ? 0 : minX;
    maxY = (maxY >= tileMap[0].size() - 1) ? tileMap[0].size() - 1 : maxY;
    maxX = (maxX >= tileMap[0][0].size() - 1) ? tileMap[0][0].size() - 1 : maxX;


    // for each tile in the selected area
    for (y = minY; y <= maxY; y++) {
        for (x = minX; x <= maxX; x++) {
            // if thetile is a wall
            if ((*tileMap)[y][x] == TileType::Wall) {
                // check make rects for the tile and collide with rect
                sf::RectangleShape tmpRect;
                tmpRect.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tmpRect.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                CheckCollision(tmpRect, 0.0f);
            }
        }
    }
}


//// Collider collisions

bool Collider::CheckCollisionCentered(Collider& other, float push) {
    sf::Vector2f thisHalfSize = GetHalfSize();   
    sf::Vector2f thisPosition = GetColliderPosition();   
    
    return checkCollision(other, thisPosition, thisHalfSize, push);
}

bool Collider::CheckCollision(Collider& other, float push) {
    sf::Vector2f thisHalfSize = GetHalfSize();   
    sf::Vector2f thisPosition = GetColliderPosition() - thisHalfSize;   
    
    return checkCollision(other, thisPosition, thisHalfSize, push);
}

bool Collider::checkCollision(Collider& other, sf::Vector2f& thisPosition, sf::Vector2f& thisHalfSize, float push) {
    sf::Vector2f otherPosition = other.GetColliderPosition();   
    sf::Vector2f otherHalfSize = other.GetHalfSize();   

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f) {
        push = std::min(std::max(push, 0.0f), 1.0f);

        if (intersectX > intersectY) {
            if (deltaX > 0.0f) {
                Move(intersectX * (1.0f - push),0.0f);
                other.Move(-intersectX * push, 0.0f);
            } else {
                Move(-intersectX * (1.0f - push),0.0f);
                other.Move(intersectX * push, 0.0f);
            }
        } else {
            if (deltaY > 0.0f) {
                Move(0.0f, intersectY * (1.0f - push));
                other.Move(0.0f, -intersectY * push);
            } else {
                Move(0.0f, -intersectY * (1.0f - push));
                other.Move(0.0f, intersectY * push);
            }
        }

        return true;
    }

    return false;
}

//// Rectangle collisions

bool Collider::CheckCollisionCentered(sf::RectangleShape& rect, float push) {
    sf::Vector2f thisHalfSize = GetHalfSize();   
    sf::Vector2f thisPosition = GetColliderPosition();   
    
    return checkCollision(rect, thisPosition, thisHalfSize, push);
}

bool Collider::CheckCollision(sf::RectangleShape& rect, float push) {
    sf::Vector2f thisHalfSize = GetHalfSize();   
    sf::Vector2f thisPosition = GetColliderPosition() - thisHalfSize;   
    
    return checkCollision(rect, thisPosition, thisHalfSize, push);
}

bool Collider::checkCollision(sf::RectangleShape& rect, sf::Vector2f& thisPosition, sf::Vector2f& thisHalfSize, float push) {
    sf::Vector2f otherHalfSize = rect.getSize() / 2.0f;   
    sf::Vector2f otherPosition = rect.getPosition();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f) {
        push = std::min(std::max(push, 0.0f), 1.0f);

        if (intersectX > intersectY) {
            if (deltaX > 0.0f) {
                Move(intersectX * (1.0f - push),0.0f);
                rect.move(-intersectX * push, 0.0f);
            } else {
                Move(-intersectX * (1.0f - push),0.0f);
                rect.move(intersectX * push, 0.0f);
            }
        } else {
            if (deltaY > 0.0f) {
                Move(0.0f, intersectY * (1.0f - push));
                rect.move(0.0f, -intersectY * push);
            } else {
                Move(0.0f, -intersectY * (1.0f - push));
                rect.move(0.0f, intersectY * push);
            }
        }

        return true;
    }

    return false;
}

