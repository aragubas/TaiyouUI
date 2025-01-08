#pragma once
#include <functional>
#include "InterpolatorEasingFunction.h"

namespace TaiyouUI::Animation
{
    class Interpolator {
        double m_CurrentValue;
        double m_ElapsedTime;
        double m_Time;

        void TimeEasing();

    public:
        double Duration;
        double StartValue;
        double TargetValue;
        bool Stopped;
        InterpolatorEasingFunction EasingFunction;

        std::function<void(float)> OnValueChanged;
        std::function<void()> OnEnded;

        Interpolator();
        
        void Update(double deltaTime);
        void Restart();

    };
}
