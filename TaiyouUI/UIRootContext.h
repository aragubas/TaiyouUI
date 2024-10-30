#pragma once
#include <SDL2/SDL.h>
#include "Turk/Turk.h"


namespace TaiyouUI
{
    struct UIRootContext
    {
        SDL_Renderer *Renderer;
        SDL_Window *Window;
        Turk::Turk *Turk;
    };
}