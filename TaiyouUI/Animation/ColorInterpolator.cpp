#include "ColorInterpolator.h"
#include <functional>
using namespace TaiyouUI::Animation;

ColorInterpolator::ColorInterpolator() :
    m_rInterpolator(Interpolator()), m_gInterpolator(Interpolator()),
    m_bInterpolator(Interpolator()), m_aInterpolator(Interpolator()),
    m_CurrentColor({255, 0, 0, 255}), m_AnyValueChanged(false),
    m_InterpolatorsFinished(0)
{
    m_CurrentColor.a = 255;
    m_CurrentColor.g = 255;
    m_CurrentColor.b = 255;
    m_CurrentColor.r = 255;

    m_rInterpolator.OnValueChanged = [this](float value) {
        m_CurrentColor.r = value;
        m_AnyValueChanged = true;
    };

    m_gInterpolator.OnValueChanged = [this](float value) {
        m_CurrentColor.g = value;
        m_AnyValueChanged = true;
    };

    m_bInterpolator.OnValueChanged = [this](float value) {
        m_CurrentColor.b = value;
        m_AnyValueChanged = true;
    };

    m_aInterpolator.OnValueChanged = [this](float value) {
        m_CurrentColor.a = value;
        m_AnyValueChanged = true;
    };

    m_rInterpolator.OnEnded = std::bind(&ColorInterpolator::InterpolatorFinishedCallback, this);
    m_gInterpolator.OnEnded = std::bind(&ColorInterpolator::InterpolatorFinishedCallback, this);
    m_bInterpolator.OnEnded = std::bind(&ColorInterpolator::InterpolatorFinishedCallback, this);
    m_aInterpolator.OnEnded = std::bind(&ColorInterpolator::InterpolatorFinishedCallback, this);
}

void ColorInterpolator::InterpolatorFinishedCallback()
{
    m_InterpolatorsFinished++;

    if (m_InterpolatorsFinished == 4)
    {
        m_InterpolatorsFinished = 0;
        if (OnEnded)
        {
            OnEnded();
        }
    }
}

void ColorInterpolator::Update(double deltaTime)
{
    m_rInterpolator.Update(deltaTime);
    m_gInterpolator.Update(deltaTime);
    m_bInterpolator.Update(deltaTime);
    m_aInterpolator.Update(deltaTime);

    if (m_AnyValueChanged)
    {
        m_AnyValueChanged = false;
        if (OnValueChanged)
        {
            OnValueChanged(m_CurrentColor);
        }
    }
}

void ColorInterpolator::Restart()
{
    m_rInterpolator.Restart();
    m_gInterpolator.Restart();
    m_bInterpolator.Restart();
    m_aInterpolator.Restart();
}

void ColorInterpolator::SetEasingFunction(InterpolatorEasingFunction easingFunction)
{
    m_rInterpolator.EasingFunction = easingFunction;
    m_gInterpolator.EasingFunction = easingFunction;
    m_bInterpolator.EasingFunction = easingFunction;
    m_aInterpolator.EasingFunction = easingFunction;
}

void ColorInterpolator::SetDuration(double duration)
{
    m_rInterpolator.Duration = duration;
    m_gInterpolator.Duration = duration;
    m_bInterpolator.Duration = duration;
    m_aInterpolator.Duration = duration;
}

void ColorInterpolator::SetStartValue(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    m_rInterpolator.StartValue = r;
    m_gInterpolator.StartValue = g;
    m_bInterpolator.StartValue = b;
    m_aInterpolator.StartValue = a;
}

void ColorInterpolator::SetStartValue(SDL_Color color)
{
    m_rInterpolator.StartValue = color.r;
    m_gInterpolator.StartValue = color.g;
    m_bInterpolator.StartValue = color.b;
    m_aInterpolator.StartValue = color.a;
}

void ColorInterpolator::SetTargetValue(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    m_rInterpolator.TargetValue = r;
    m_gInterpolator.TargetValue = g;
    m_bInterpolator.TargetValue = b;
    m_aInterpolator.TargetValue = a;
}

void ColorInterpolator::SetTargetValue(SDL_Color color)
{
    m_rInterpolator.TargetValue = color.r;
    m_gInterpolator.TargetValue = color.g;
    m_bInterpolator.TargetValue = color.b;
    m_aInterpolator.TargetValue = color.a;
}