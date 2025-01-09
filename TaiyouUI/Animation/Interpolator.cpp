#include "Interpolator.h"
#include "TaiyouUI/Animation/InterpolatorEasingFunction.h"
using namespace TaiyouUI::Animation;

Interpolator::Interpolator() :
    Duration(1), m_CurrentValue(0),
    StartValue(0), TargetValue(0),
    m_ElapsedTime(0), m_Time(0),
    Stopped(false), EasingFunction(InterpolatorEasingFunction::SmoothEaseInOut)
{
    
}

void Interpolator::Update(double deltaTime)
{
    if (Stopped)
        return;
    
    // Advance time forward
    m_ElapsedTime += deltaTime;
    
    // Normalize time between 0 and 1
    m_Time = m_ElapsedTime / Duration;

    // Detect when animation has finished
    if (m_Time >= 1.0f)
    {
        m_Time = 1.0f;
        Stopped = true;
        m_CurrentValue = TargetValue;

        if (OnEnded)
            OnEnded();

        return;
    }

    // Apply time easing function
    TimeEasing();

    m_CurrentValue = StartValue + (TargetValue - StartValue) * m_Time;

    if (OnValueChanged)
        OnValueChanged(m_CurrentValue);
}

void Interpolator::TimeEasing()
{
    switch (EasingFunction)
    {
        case (InterpolatorEasingFunction::SmoothEaseInOut):
        {
            m_Time = m_Time * m_Time * (3 - 2 * m_Time);
            break;
        }

        case (InterpolatorEasingFunction::Linear): 
        {
            // Literally don't do anything if it's linear
            break;
        }
    }
}

void Interpolator::Restart()
{
    m_Time = 0;
    m_ElapsedTime = 0;
    m_CurrentValue = StartValue;
    Stopped = false;
}