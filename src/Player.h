#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Entity.h"

// define PLayer as child of entity
class Player : public Entity {
public:
    Player(sf::Texture* texture, sf::RenderWindow* window, sf::Vector2u imageCount, float switchTime, float speed);
    void Update(float* deltaTime) override;

private:
    sf::Vector2f lastMovement;
};

#endif
