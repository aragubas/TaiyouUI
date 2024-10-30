#pragma once
#include <SDL.h>


namespace TaiyouUI
{
    struct InputEvent
    {
        bool IsKeyboardEvent;
        bool IsGamepadEvent;
    };
}