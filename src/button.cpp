// button GUI object

#include <iostream>
#include <string>

#include "include/button.hpp"

#include <sdl2/include/SDL.h>
#include "include/window.hpp"

SDL_Texture *roundedBtn;
bool first = false;

// create a GUI button
GUIButton::GUIButton(int x, int y, int width, int height, int r, int g, int b,
                     int fR, int fG, int fB, int fontSize, std::string text, bool rounded)
{
    if (!first) // make sure that we aren't loading the rounded button texture every time we want a new button
    {
        first = true;
        roundedBtn = Window::loadImage("res/gfx/rounded_btn.png");
    }

    // actual position
    pos = {x, y, width, height};

    // background color
    this->r = r;
    this->g = g;
    this->b = b;

    this->rounded = rounded; // set its rounded state for rendering
    font = Window::loadFont("res/gfx/font.ttf", fontSize, text.c_str(), fR, fG, fB);
}

void GUIButton::render()
{
    // center the button text to be in the center of the button
    int posX = pos.x + (pos.w / 2) - (Window::getTextureSize(font).width / 2);
    int posY = pos.y + (pos.h / 2) - (Window::getTextureSize(font).height / 2);

    if (!rounded) // if it isn't rounded, then just draw a simple rectangle
    {
        Window::drawRectangle(pos, r, g, b);
    }

    if (first == true) // if it is, draw the rounded version
    {
        SDL_SetTextureColorMod(roundedBtn, r, g, b); // special SDL2 function to change the color of the white button
        Window::drawImage(roundedBtn, pos.x, pos.y, pos.w, pos.h);
    }

    Window::drawFont(font, posX, posY);
}

// check if the user has the mouse over the button
bool GUIButton::pressed(int mouseX, int mouseY)
{
    SDL_Point mousePos = {mouseX, mouseY};
    return SDL_PointInRect(&mousePos, &pos);
}