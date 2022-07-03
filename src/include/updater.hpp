#pragma once
#include <sdl2/include/SDL_ttf.h>

namespace Updater
{
    bool check();
    void update(bool &finishedUpdating, bool &finishedDownloading);
};