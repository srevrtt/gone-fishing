#include <iostream>
#include <string>

#include <sdl2/include/SDL.h>
#include <sdl2/include/SDL_image.h>
#include <sdl2/include/SDL_ttf.h>

#include "include/window.hpp"

// since we will only have one window, defining these global
SDL_Window *window;
SDL_Renderer *renderer;

// for security
bool windowCreated = false;

// create the window
void Window::create(int width, int height, const char *title)
{
    if (windowCreated == false)
    {
        windowCreated = true; // make sure only one window can be created

        // init SDL2
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();

        // create the window
        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_SHOWN);

        // error handling
        if (!window)
        {
            std::cout << "Error creating an SDL2 window.\n";
            exit(0);
        }

        // create a renderer for drawing graphics
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (!renderer)
        {
            std::cout << "Error creating an SDL2 renderer.\n";
            exit(0);
        }

        // change window color to a light blue
        SDL_SetRenderDrawColor(renderer, 40, 201, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}

// load an image for drawing
SDL_Texture *Window::loadImage(const char *filepath)
{
    SDL_Surface *image = IMG_Load(filepath);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_FreeSurface(image);
    return texture;
}

SDL_Texture *Window::loadFont(const char *filepath, int size, const char *text, int r, int g, int b)
{
    SDL_Color color = {r, g, b};
    TTF_Font *font = TTF_OpenFont(filepath, size);

    SDL_Surface *sur = TTF_RenderText_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, sur);

    SDL_FreeSurface(sur);
    return texture;
}

TTF_Font *Window::loadFontRaw(const char *filepath, int size)
{
    return TTF_OpenFont(filepath, size);
}

void Window::drawFontRaw(TTF_Font *font, const char *text, int x, int y, int r, int g, int b)
{
    SDL_Color color = {r, g, b};

    SDL_Surface *sur = TTF_RenderText_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, sur);

    int width, height = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SDL_Rect pos = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &pos);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(sur);
}

void Window::drawFont(SDL_Texture *texture, int x, int y)
{
    int width, height;

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SDL_Rect pos = {x, y, width, height};

    SDL_RenderCopy(renderer, texture, nullptr, &pos);
}

// draw the loaded image into the screen
void Window::drawImage(SDL_Texture *image, int x, int y, int width, int height)
{
    SDL_Rect pos = {x, y, width, height};
    SDL_RenderCopy(renderer, image, nullptr, &pos); // actually draw the pixels
}

// draw the fish with special rotation
void Window::drawFish(SDL_Texture *image, int x, int y, int width, int height, int direction)
{
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (direction == 1)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }

    SDL_Rect pos = {x, y, width, height};
    SDL_RenderCopyEx(renderer, image, nullptr, &pos, 0, nullptr, flip); // draw the pixels with rotation
}

// create a rectangle for a fishing rod
void Window::drawRectangle(SDL_Rect rect, int r, int g, int b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 40, 201, 255, 255);
}

// get texture size for drawing fonts
Size Window::getTextureSize(SDL_Texture *texture)
{
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    Size size = {width, height};
    return size;
}

// clear the renderer every frame
void Window::clear()
{
    SDL_RenderClear(renderer);
}

// render everything to the screen
void Window::display()
{
    SDL_RenderPresent(renderer);
}

// close the window
void Window::close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}