#pragma once
#include <SDL2/SDL.h>
#include "Control.h"
#include "UIRootContext.h"


namespace TaiyouUI
{
    class Control
    {
    public:
        UIRootContext *Context;
        Control *ParentControl;
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

        /// @brief If the control should be rendered
        bool IsVisible = true;

        /// @brief If the control is enabled
        bool IsEnabled = true;

        Control();

        virtual void Update(double deltaTime) = 0;
        virtual void EventUpdate(SDL_Event &event) = 0;
        void Draw(SDL_Renderer *renderer, double deltaTime);

    private:
        virtual void OnDraw(SDL_Renderer *renderer, double deltaTime) = 0;
    };
}
