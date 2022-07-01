#include <iostream>
#include <string>
#include <vector>

#include <sdl2/include/SDL.h>

#include "include/window.hpp"
#include "include/fish.hpp"
#include "include/button.hpp"
#include "include/gui.hpp"
#include "include/fishManager.hpp"

SDL_Event event; // window events (mouse, keyboard, etc.)

// timer
double timer = 0.00;
float previousCooldown = 0.0f;

// fps limiting variables
const int frameDelay = 1000 / 60;
Uint32 frameStart;
int frameTime;

// for delta time calculation
Uint64 LAST;
Uint64 NOW;
double deltaTime;

bool fishCaught = false;
int state = 1;

int fishCount = 10;

int main(int argc, char **args)
{
    Window::create(1280, 720, "Gone Fishing v1.0.0-rc.1");
    std::vector<SDL_Texture *> otherTextures;

    TTF_Font *font = Window::loadFontRaw("res/gfx/font.ttf", 30);

    // to prevent high cpu & memory usage, load these before the game loop instead of every frame
    otherTextures.push_back(Window::loadImage("res/gfx/water.png"));
    otherTextures.push_back(Window::loadImage("res/gfx/waves.png"));

    Gui::init();            // initiate GUI elements
    FishManager::genFish(); // generate each fish

    // rod position
    SDL_Rect rod = {300, -200, 3, 720};

    NOW = SDL_GetPerformanceCounter();

    // game loop
    while (true)
    {
        frameStart = SDL_GetTicks();

        Window::clear(); // clear the renderer

        // delta time precalculation
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        // event handling
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) // when the user closes the window
        {
            break;
        }

        if (event.type == SDL_MOUSEMOTION) // if the user moves the mouse
        {
            // move the rod to the mouse's position
            rod.x = event.motion.x;
            rod.h = event.motion.y + 200;
        }

        if (event.type == SDL_MOUSEBUTTONUP) // if the user clicks their mouse button
        {
            SDL_Point p = {event.motion.x, event.motion.y}; // store the mouse position

            // get each fish
            for (auto &fish : FishManager::getFishes())
            {
                if (fish->hidden == true) // we don't want the hidden fish
                {
                    continue;
                }

                SDL_Rect rect = fish->getHitbox(); // get the fish's hitbox for fishing mechanic

                if (SDL_PointInRect(&p, &rect) && fishCaught == false) // if the user's mouse is inside the hitbox
                {
                    fishCaught = true;
                    fish->changeDirection(IDLE); // stop the fish
                }

                // if the user clicks above the water with the fish
                if (fish->getDirection() == 0 && fish->y < 320 && fishCaught == true)
                {
                    fishCaught = false;
                    fish->hidden = true; // hide the fish
                    fishCount--;
                }
            }

            Gui::handleEvents(event.motion.x, event.motion.y, state); // modify the state when each button is pressed

            if (state == -1)
            {
                break;
            }
        }

        // increment the timer
        if ((SDL_GetTicks() - previousCooldown > 0.001) && state == 0)
        {
            previousCooldown = SDL_GetTicks();
            timer += 0.02;
        }

        // delta time calculation
        deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

        // draw each texture
        Window::drawImage(otherTextures[0], 0, 360, 1280, 360);
        Window::drawImage(otherTextures[1], 0, 320, 1280, 40);

        // if the player is playing the game, handle everything
        if (state == 0)
        {
            FishManager::move(deltaTime, fishCaught, rod);
            FishManager::render(state, fishCount, timer);

            // TODO: more efficient algorithm here
            std::string timerText = std::to_string(timer);
            timerText.pop_back();
            timerText.pop_back();
            timerText.pop_back();
            timerText.pop_back();

            Window::drawRectangle(rod, 0, 0, 0); // draw the rod rectangle with a color of black

            Window::drawFontRaw(font, timerText.c_str(), 612, 33, 0, 0, 0);       // draw detail
            Window::drawFontRaw(font, timerText.c_str(), 612, 30, 255, 255, 255); // draw main part
        }

        // if the user is at the start screen
        if (state == 1)
        {
            Gui::renderStartScreen();
        }

        // if the user is at the end screen
        if (state == 2)
        {
            Gui::renderEndScreen();
        }

        Window::display();

        // fps limiting (to reduce CPU and GPU usage)
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // once we're done, close the window
    Window::close();

    return 0;
}