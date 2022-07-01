// file for the fish object

#include <iostream>
#include <string>
#include <cstdlib>

#include <sdl2/include/SDL.h>
#include "include/fish.hpp"

const float fishSpeed = 0.2f;

// create a new fish (fish constructor)
Fish::Fish(int x, int y)
{
    this->x = x;
    this->y = y;

    // set the randomized fish direction
    int r = rand() % 2 + 1;

    if (r == 1)
    {
        direction = -1;
    }

    if (r == 2)
    {
        direction = 1;
    }

    renderDirection = direction;
    fishColor = rand() % 5; // generate a random fish color
}

// update the fish every frame
void Fish::update(double deltaTime)
{
    x += fishSpeed * direction * deltaTime;
    hitbox = {this->x - 31, this->y - 5, 63, 41}; // hitbox system to make it easier for the player to catch a fish
}

// change the fish's direction
void Fish::changeDirection(int direction)
{
    switch (direction)
    {
    case LEFT:
        this->direction = -1;
        renderDirection = -1;

        break;
    case RIGHT:
        this->direction = 1;
        renderDirection = 1;

        break;
    case IDLE: // reset the direction but keep the render direction (so that the fish don't change direction when caught)
        this->direction = 0;
        break;
    }
}

// get the fish's fake direction (for fish rendering)
int Fish::getRenderDirection()
{
    return renderDirection;
}

// get the fish's direction (for fishing mechanic)
int Fish::getDirection()
{
    return direction;
}

// get the fish's color (for fish rendering)
int Fish::getColor()
{
    return fishColor;
}

// get the fish's hitbox (for fishing rod)
SDL_Rect Fish::getHitbox()
{
    return hitbox;
}