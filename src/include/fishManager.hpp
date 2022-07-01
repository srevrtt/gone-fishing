#pragma once

#include <vector>
#include <sdl2/include/SDL.h>

#include "fish.hpp"

namespace FishManager
{
    void genFish();

    void render(int &state, int &fishCount, double &timer);
    void move(double deltaTime, bool fishCaught, SDL_Rect rod);

    std::vector<Fish *> getFishes();
}