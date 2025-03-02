#pragma once
#include <SDL3/SDL.h>
#include "Turk/Turk.h"


namespace TaiyouUI
{
    struct UIRootContext
    {
        std::shared_ptr<SDL_Renderer> Renderer;
        std::shared_ptr<SDL_Window> Window;
        std::shared_ptr<TurkInstance> Turk;
    };
}