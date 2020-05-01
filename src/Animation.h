// Animation.h
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

// defines the class for an animation
class Animation {
public:
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;

public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Animation();
    
    void Update(int row, float* deltaTime);
};

#endif

