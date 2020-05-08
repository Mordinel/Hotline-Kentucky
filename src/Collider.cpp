#include "Collider.h"

Collider::Collider(sf::RectangleShape& boundary, std::vector<std::vector<TileType>>* tileMap) : boundary(boundary) {
    this->tileMap = tileMap;
}

Collider::~Collider() {

}

// check for square intersecs and move objects
bool Collider::CheckCollision(Collider& other, float push) {
    sf::Vector2f otherPosition = other.GetColliderPosition();   
    sf::Vector2f otherHalfSize = other.GetHalfSize();   

    sf::Vector2f thisPosition = GetColliderPosition();   
    sf::Vector2f thisHalfSize = GetHalfSize();   

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

void Collider::checkTilemapCollision(sf::Vector2f movement) {
    float halfWidth = boundary.getSize().x / 2.0f;
    float halfHeight = boundary.getSize().y / 2.0f;
    float tileSize = 32.0f;

    sf::Vector2f thisPosition = GetColliderPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    sf::RectangleShape topLeft;
    sf::RectangleShape topRight;
    sf::RectangleShape bottomLeft;
    sf::RectangleShape bottomRight;

    topLeft.setSize(sf::Vector2f(tileSize, tileSize));
    topRight.setSize(sf::Vector2f(tileSize, tileSize));
    bottomLeft.setSize(sf::Vector2f(tileSize, tileSize));
    bottomRight.setSize(sf::Vector2f(tileSize, tileSize));

    topLeft.setPosition((float)(int)(boundary.getPosition().x - halfWidth), (int)(boundary.getPosition().y - halfHeight));
    topRight.setPosition((float)(int)(boundary.getPosition().x + halfWidth), (int)(boundary.getPosition().y - halfHeight));
    bottomLeft.setPosition((float)(int)(boundary.getPosition().x - halfWidth), (int)(boundary.getPosition().y + halfHeight));
    bottomRight.setPosition((float)(int)(boundary.getPosition().x + halfWidth), (int)(boundary.getPosition().y + halfHeight));

    bool tl = (*tileMap)[(int)(topLeft.getPosition().y / tileSize)][(int)(topLeft.getPosition().x / tileSize)] == TileType::Wall;
    bool tr = (*tileMap)[(int)(topRight.getPosition().y / tileSize)][(int)(topRight.getPosition().x / tileSize)] == TileType::Wall;
    bool bl = (*tileMap)[(int)(bottomLeft.getPosition().y / tileSize)][(int)(bottomLeft.getPosition().x / tileSize)] == TileType::Wall;
    bool br = (*tileMap)[(int)(bottomRight.getPosition().y / tileSize)][(int)(bottomRight.getPosition().x / tileSize)] == TileType::Wall;

    float piBoundX = boundary.getSize().x / 3.14;
    float piBoundY = boundary.getSize().y / 3.14;

    //concave corners
    if (tl && bl && tr) {
        boundary.setPosition(topLeft.getPosition().x + topLeft.getSize().x - piBoundX,
                            (topLeft.getPosition().y + topLeft.getSize().y - piBoundX));
    } else if (tr && tl && br) {
        boundary.setPosition(topRight.getPosition().x - (piBoundX * 2.0f),
                            (topRight.getPosition().y + topRight.getSize().y - piBoundY));
    } else if (bl && tl && br) {
        boundary.setPosition(bottomLeft.getPosition().x + bottomLeft.getSize().x - piBoundX,
                             bottomLeft.getPosition().y - (piBoundY * 2.0f));
    } else if (br && tr && bl) {
        boundary.setPosition(bottomRight.getPosition().x - (piBoundX * 2.0f),
                             bottomRight.getPosition().y - (piBoundY * 2.0f));
   // edges
    } else if (tl && bl) {         // left
        boundary.setPosition((topLeft.getPosition().x + topLeft.getSize().x) - piBoundX, boundary.getPosition().y);
    } else if (tl && tr) {  // top
        boundary.setPosition(boundary.getPosition().x, (topLeft.getPosition().y + topLeft.getSize().y) - piBoundY);
    } else if (tr && br) {  // right
        boundary.setPosition((topRight.getPosition().x - boundary.getSize().x) + piBoundX + 1.0f, boundary.getPosition().y);
    } else if (bl && br) {  // bottom
        boundary.setPosition(boundary.getPosition().x, (bottomLeft.getPosition().y - boundary.getSize().y) + piBoundY + 1.0f);

    // convex corners
    } else if (tl) {        // top left
        boundary.setPosition((topLeft.getPosition().x + topLeft.getSize().x - piBoundX),
                            ((topLeft.getPosition().y + topLeft.getSize().y - piBoundY)));
    } else if (tr) {        // top right
        boundary.setPosition(topRight.getPosition().x - (piBoundX * 2.0f),
                            (topRight.getPosition().y + topRight.getSize().y - piBoundY));
    } else if (bl) {        // bottom left
        boundary.setPosition(bottomLeft.getPosition().x + bottomLeft.getSize().x - piBoundX,
                             bottomLeft.getPosition().y - (piBoundY * 2.0f));
    } else if (br) {        // bottom right
        boundary.setPosition(bottomRight.getPosition().x - (piBoundX * 2.0f),
                             bottomRight.getPosition().y - (piBoundY * 2.0f));
    }
}

