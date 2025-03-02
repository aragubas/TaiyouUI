#pragma once
#include "Interpolator.h"
#include "TaiyouUI/Animation/InterpolatorEasingFunction.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_stdinc.h>

namespace TaiyouUI::Animation
{
    class ColorInterpolator 
    {
        Interpolator m_rInterpolator;
        Interpolator m_gInterpolator;
        Interpolator m_bInterpolator;
        Interpolator m_aInterpolator;
        SDL_Color m_CurrentColor;
        bool m_AnyValueChanged;
        unsigned char m_InterpolatorsFinished;

        void InterpolatorFinishedCallback();

    public:
        ColorInterpolator();

        void Update(double deltaTime);
        void Restart();

        void SetEasingFunction(InterpolatorEasingFunction easingFunction);
        void SetDuration(double duration);
        void SetStartValue(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void SetStartValue(SDL_Color color);
        void SetTargetValue(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void SetTargetValue(SDL_Color color);
        std::function<void(SDL_Color)> OnValueChanged;
        std::function<void()> OnEnded;
    };
}