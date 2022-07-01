#pragma once

#include <vector>

#include <sdl2/include/SDL.h>
#include <sdl2/include/SDL_ttf.h>

struct Size
{
    int width, height;
};

namespace Window
{
    void create(int width, int height, const char *title);

    SDL_Texture *loadImage(const char *filepath);
    SDL_Texture *loadFont(const char *filepath, int size, const char *text, int r, int g, int b);

    TTF_Font *loadFontRaw(const char *filepath, int size);
    void drawFontRaw(TTF_Font *font, const char *text, int x, int y, int r, int g, int b);

    void drawImage(SDL_Texture *texture, int x, int y, int width, int height);
    void drawFont(SDL_Texture *texture, int x, int y);
    void drawFish(SDL_Texture *texture, int x, int y, int width, int height, int direction);

    void drawRectangle(SDL_Rect rect, int r, int g, int b);
    Size getTextureSize(SDL_Texture *texture);

    void clear();
    void display();

    void close();
} // namespace Window
