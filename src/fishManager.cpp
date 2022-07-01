// file to handle the main fish mechanics

#include <iostream>
#include <string>
#include <vector>

#include <sdl2/include/SDL.h>

#include "include/fishManager.hpp"
#include "include/fish.hpp"
#include "include/window.hpp"

std::vector<Fish *> fishes;
std::vector<SDL_Texture *> fishTextures;

float fishSpawnCooldown = 2000.0f; // respawn fish every 2 seconds
float previousFishSpawnCooldown = 0.0f;

// fish generation
void FishManager::genFish()
{
    srand(time(0)); // gen a random seed

    // fish position generation
    for (int i = 0; i < 10; i++)
    {
        int x = rand() % 1100 + 50;
        int y = rand() % 350 + 350;

        fishes.push_back(new Fish(x, y));
    }

    // like with the water, do all of this before
    for (auto &fish : fishes)
    {
        std::string id = std::to_string(fish->getColor());
        fishTextures.push_back(Window::loadImage(("res/gfx/fish_" + id + ".png").c_str()));
    }
}

// render the fish & game state handling
void FishManager::render(int &state, int &fishCount, double &timer)
{
    if (fishCount == 0)
    {
        fishes.clear();

        // fish position generation
        for (int i = 0; i < 10; i++)
        {
            int x = rand() % 1100 + 50;
            int y = rand() % 350 + 350;

            fishes.push_back(new Fish(x, y));
        }

        // like with the water, do all of this before
        for (auto &fish : fishes)
        {
            std::string id = std::to_string(fish->getColor());
            fishTextures.push_back(Window::loadImage(("res/gfx/fish_" + id + ".png").c_str()));
        }

        state = 2;      // set the state to an end state
        fishCount = 10; // reset the amount of fish
        timer = 0.00;   // reset the timer
    }

    // respawning system with a cooldown
    if (fishCount < 10 && SDL_GetTicks() - previousFishSpawnCooldown > fishSpawnCooldown && state == 0)
    {
        previousFishSpawnCooldown = SDL_GetTicks();

        // generate random position
        int x = rand() % 1100 + 50;
        int y = rand() % 350 + 350;

        // create a new fish
        Fish *fish = new Fish(x, y);
        fishes.push_back(fish);

        // get the id of the fish for its random color
        std::string id = std::to_string(fish->getColor());
        fishTextures.push_back(Window::loadImage(("res/gfx/fish_" + id + ".png").c_str()));

        fishCount++; // add a new fish
    }
}

// move each fish
void FishManager::move(double deltaTime, bool fishCaught, SDL_Rect rod)
{
    // fish moving logic
    for (unsigned int i = 0; i < fishes.size(); i++)
    {
        Fish *fish = fishes[i];
        fish->update(deltaTime);

        // if the fish is too far left, move right
        if (fish->x < 50 && fish->getDirection() != 0)
        {
            fish->changeDirection(RIGHT);
        }

        // if the fish is too far right, move left
        if (fish->x > 1200 && fish->getDirection() != 0)
        {
            fish->changeDirection(LEFT);
        }

        // if the fish is caught, move it with the rod
        if (fish->getDirection() == 0 && fishCaught == true && fish->hidden == false)
        {
            fish->x = rod.x;
            fish->y = rod.h - 200;
        }

        // if the fish isn't caught, render it
        if (fish->hidden == false)
        {
            Window::drawFish(fishTextures[i], fish->x - 29, fish->y, 58, 36, fish->getRenderDirection());
        }
    }
}

// get the fishes for event handling
std::vector<Fish *> FishManager::getFishes()
{
    return fishes;
}