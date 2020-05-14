/******************************************************************************
 * Filename: Animation.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 01/05/2020
 * Description: Handles the animations in the game.
 *****************************************************************************/

#include <SFML/Graphics.hpp>
#include "Animation.h"

/*
 * Constructor for the Animation class
 * 
 * Parameters:
 *      texture - the texture that contain the animation frames
 *      imageCount - a vector storing how many rows and cols of frames are in the texture
 *      switchTime - the amount of time a frame is displayed before it goes to the next frame 
 */
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

/*
 * Destructor for the Animation class
 */
Animation::~Animation() {
    
}

/*
 * Updates the animation frame by moving the texture coordinates to the next part of the texture
 * when it's time. (total time elaspsed since last frame is larger than switch time)
 * 
 * Parameters:
 *      row - the row of the texture that should be displayed
 *      deltaTime - how much time has passed since last game loop
 */
void Animation::Update(int row, float* deltaTime) {
    currentImage.y = row;
    totalTime += *deltaTime;
    
    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x) {
            currentImage.x = 0;
        }
    }

    uvRect.top = currentImage.y * uvRect.height;
    uvRect.left = currentImage.x * abs(uvRect.width);
    uvRect.width = abs(uvRect.width);
}

