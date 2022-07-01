#pragma once
#include <string>

#include <sdl2/include/SDL.h>

class GUIButton
{
private:
    SDL_Rect pos;
    SDL_Texture *font;
    int r, g, b;

    std::string text;

    bool rounded = false;

public:
    GUIButton(int x, int y, int width, int height, int r, int g, int b,
              int fR, int fG, int fB, int fontSize, std::string text, bool rounded);

    void render();
    bool pressed(int mouseX, int mouseY);
};