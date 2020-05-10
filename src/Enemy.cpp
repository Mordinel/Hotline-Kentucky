#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap) : Entity(texture, window, imageCount, switchTime, speed, tileMap) {
    state = (EnemyState)(std::rand() % 2);
}