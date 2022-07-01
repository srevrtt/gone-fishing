#pragma once

enum FishDirection
{
    LEFT,
    RIGHT,
    IDLE
};

class Fish
{
private:
    int direction, renderDirection, fishColor;
    SDL_Rect hitbox;

public:
    int x, y;
    bool hidden = false;

    Fish(int x, int y);

    void update(double deltaTime);
    void changeDirection(int direction);

    int getDirection();
    int getRenderDirection();

    int getColor();

    SDL_Rect getHitbox();
};