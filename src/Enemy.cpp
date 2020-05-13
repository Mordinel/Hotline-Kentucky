#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap) : Entity(texture, window, imageCount, switchTime, speed, tileMap) {
    state = (EnemyState)(std::rand() % 2);
}

void Enemy::Die() {
    this->state = EnemyState::Dead;

}


void Enemy::Update(float* deltaTime, sf::Vector2f playerPos) {
    sf::Vector2f currentPos = body.getPosition();
    sf::Vector2f deltaPos = playerPos - currentPos;

    float xMove, yMove;
    if (deltaPos.x > 1) {
        xMove = speed;
    } else {
        xMove = speed * -1;
    }

    if (deltaPos.y > 1) {
        yMove = speed;
    } else {
        yMove = speed * -1;
    }

    sf::Vector2f movement(xMove, yMove);
    

    animation.Update(row, deltaTime);
    body.setTextureRect(animation.uvRect);

    body.move(movement);

    checkCollisionsNearBody();
}