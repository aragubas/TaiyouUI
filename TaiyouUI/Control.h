#pragma once
#include <SDL2/SDL.h>
#include "UIRootContext.h"


namespace TaiyouUI
{

    enum ControlVisibility : char 
    {
        /// @brief Visible and Enabled (control is rendered and processes input)
        VisibleEnabled,
        /// @brief Visible but disabled (control is rendered but doesn't process input)
        VisibleDisabled,
        /// @brief Control is invisible and disabled (control is invisible and doesn't process any inputs)
        Invisible
    };

    /// Base class for controls
    class Control
    {
    public:
        UIRootContext Context;
        Control *ParentControl;
        /// @brief Relative position inside parent container
        SDL_FPoint RelativePosition;

        /// @brief Absolute position on screen
        SDL_FPoint AbsolutePosition;

        /// @brief Minimum Size
        SDL_FPoint MinimumSize;

        /// @brief Maximum Size
        SDL_FPoint MaximumSize;

        /// @brief Size of the internal border from content to control box
        SDL_FPoint Padding;

        /// @brief Total size (including padding)
        SDL_FPoint Size;

        /// @brief Control State
        ControlVisibility Visibility;

        Control(const UIRootContext& context, Control* parentControl = nullptr);

        virtual void Update(double deltaTime) = 0;
        virtual void EventUpdate(SDL_Event &event) = 0;
        void Draw(SDL_Renderer *renderer, double deltaTime);

    private:
        virtual void OnDraw(SDL_Renderer *renderer, double deltaTime) = 0;
    };
}
