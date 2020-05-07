#include "Collider.h"

Collider::Collider(sf::RectangleShape& boundary) : boundary(boundary) {
    
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
