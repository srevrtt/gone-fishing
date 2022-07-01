// gui file for ingame gui

#include <iostream>
#include <string>

#include <sdl2/include/SDL.h>

#include "include/gui.hpp"
#include "include/button.hpp"
#include "include/window.hpp"

// play button with a black outline on the bottom (for the start screen)
GUIButton *play;
GUIButton *playOutline;

// back button with a black outline on the bottom (for the end screen)
GUIButton *back;
GUIButton *backOutline;

// quit button (for both screens)
GUIButton *quit;
GUIButton *quitOutline;

// title text with the same effect as the buttons (for the start screen)
SDL_Texture *title;
SDL_Texture *titleEffect;

// "you won" text with the same effect as the buttons (for the end screen)
SDL_Texture *youWon;
SDL_Texture *youWonEffect;

// initiate everything after the SDL2 context has been created
void Gui::init()
{
    // hardcoding everything for now

    play = new GUIButton(452, 300, 375, 100, 240, 240, 240, 0, 0, 0, 35, "Play", true);
    playOutline = new GUIButton(452, 300, 375, 105, 0, 0, 0, 0, 0, 0, 35, "", true);

    back = new GUIButton(452, 300, 375, 100, 240, 240, 240, 0, 0, 0, 35, "Back", true);
    backOutline = new GUIButton(452, 300, 375, 105, 0, 0, 0, 0, 0, 0, 35, "", true);

    quit = new GUIButton(452, 450, 375, 100, 240, 240, 240, 0, 0, 0, 35, "Quit", true);
    quitOutline = new GUIButton(452, 450, 375, 105, 0, 0, 0, 0, 0, 0, 35, "", true);

    title = Window::loadFont("res/gfx/font.ttf", 60, "Gone Fishing", 255, 255, 255);
    titleEffect = Window::loadFont("res/gfx/font.ttf", 60, "Gone Fishing", 0, 0, 0);

    youWon = Window::loadFont("res/gfx/font.ttf", 60, "You won!", 255, 255, 255);
    youWonEffect = Window::loadFont("res/gfx/font.ttf", 60, "You won!", 0, 0, 0);
}

// render the end screen when the player wins the game
void Gui::renderEndScreen()
{
    // center the text
    int effectX = (1280 / 2) - (Window::getTextureSize(youWon).width / 2);
    int regularX = (1280 / 2) - (Window::getTextureSize(youWonEffect).width / 2);

    // draw each font
    Window::drawFont(youWonEffect, effectX, 53);
    Window::drawFont(youWon, regularX, 50);

    // render each button
    backOutline->render();
    back->render();

    quitOutline->render();
    quit->render();
}

// render the start screen when the player runs the game or when the player presses the back button on the end screen
void Gui::renderStartScreen()
{
    // center the text
    int effectX = (1280 / 2) - (Window::getTextureSize(titleEffect).width / 2);
    int regularX = (1280 / 2) - (Window::getTextureSize(title).width / 2);

    // draw each font
    Window::drawFont(titleEffect, effectX, 53);
    Window::drawFont(title, regularX, 50);

    playOutline->render();
    play->render();

    quitOutline->render();
    quit->render();
}

// handle the button events
void Gui::handleEvents(int x, int y, int &state)
{
    // if the play button is pressed and the game is in its starting state
    if (play->pressed(x, y) && state == 1)
    {
        state = 0;
    }

    // if the back button is pressed and the game is in its ending state
    if (back->pressed(x, y) && state == 2)
    {
        state = 1;
    }

    // if the quit button is pressed and the game is either in its ending state or its starting state
    if (quit->pressed(x, y) && (state == 1 || state == 2))
    {
        state = -1;
    }
}