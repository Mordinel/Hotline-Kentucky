#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "PlayerState.h"

// define PLayer as child of entity and Collider
class Player : public Entity {
public:
    Player(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed, std::vector<std::vector<TileType>>* tileMap);
    void Update(float* deltaTime) override;
    PlayerState GetState();

private:
    sf::Vector2f lastMovement;
    PlayerState state;
};

#endif
