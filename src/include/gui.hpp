#pragma once

namespace Gui
{
    void init();

    void renderEndScreen();
    void renderStartScreen();

    void handleEvents(int x, int y, int &state);
}