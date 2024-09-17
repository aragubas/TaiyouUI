#pragma once
#include <SDL2/SDL.h>
#include "Control.h"

class Control
{    
public:
    Control* ParentControl;
    /// @brief Relative position inside parent container
    SDL_FPoint RelativePosition;
    
    /// @brief Absolute position on screen
    SDL_FPoint AbsolutePosition;
    
    /// @brief Minimum Size
    SDL_FPoint MinimumSize;
    
    /// @brief Maximum Size
    SDL_FPoint MaximumSize;
    
    /// @brief Total Pixel size
    SDL_FPoint Size;

    
    virtual void Update(double deltaTime) = 0;
    virtual void Draw(SDL_Renderer* renderer, double deltaTime) = 0;
};