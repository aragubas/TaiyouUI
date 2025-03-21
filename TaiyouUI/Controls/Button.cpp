#include "Button.h"
#include "TaiyouUI/Animation/ColorInterpolator.h"
#include "TaiyouUI/Control.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace TaiyouUI;

// Color Scheme
const SDL_Color Controls::Button::s_ColorBackgroundIdle = {59, 40, 75, 255};
const SDL_Color Controls::Button::s_ColorBackgroundHovering = {59, 40, 75, 255};
const SDL_Color Controls::Button::s_ColorBackgroundPressed = { 101, 82, 117, 255};
const SDL_Color Controls::Button::s_ColorBackgroundDisabled = { 36, 19, 51, 255 };

const SDL_Color Controls::Button::s_ColorForegroundIdle = {228, 228, 228, 255};
const SDL_Color Controls::Button::s_ColorForegroundHovering = {243, 243, 243, 255};
const SDL_Color Controls::Button::s_ColorForegroundPressed = {255, 255, 255, 255};
const SDL_Color Controls::Button::s_ColorForegroundDisabled = { 200, 200, 200, 255 };

const SDL_Color Controls::Button::s_ColorBorderIdle = {36, 19, 51, 255};
const SDL_Color Controls::Button::s_ColorBorderHovering = {101, 82, 117, 255};
const SDL_Color Controls::Button::s_ColorBorderPressed = { 150, 138, 160, 255};
const SDL_Color Controls::Button::s_ColorBorderDisabled = { 59, 40, 75, 255 };


Controls::Button::Button(const UIRootContext& context, const std::string& text, Control* parentControl) :
    Control(context, parentControl), // Base Constructor
    OnClick(std::function<void()>()), m_TextTexture(nullptr), m_TextTextureSize(SDL_Point()),
    m_Font(FontDescriptor()),
    m_CurrentBackgroundColor(s_ColorBackgroundIdle),
    m_CurrentBackgroundColorInterpolator(Animation::ColorInterpolator()),
    m_CurrentForegroundColor(s_ColorForegroundIdle), 
    m_CurrentForegroundColorInterpolator(Animation::ColorInterpolator()),
    m_CurrentBorderColor(s_ColorBorderIdle),
    m_CurrentBorderColorInterpolator(Animation::ColorInterpolator()),
    m_CurrentState(TaiyouButtonState::Disabled), m_LastState(TaiyouButtonState::Disabled),
    m_Text(std::string())
{
    Padding = SDL_FPoint();
    Padding.x = 12;
    Padding.y = 4;
    
    m_CurrentBackgroundColorInterpolator.SetDuration(0.20);
    m_CurrentForegroundColorInterpolator.SetDuration(0.20);
    m_CurrentBorderColorInterpolator.SetDuration(0.20);

    m_CurrentBackgroundColorInterpolator.OnValueChanged = [this](SDL_Color color) {
        m_CurrentBackgroundColor = color;
    };

    m_CurrentForegroundColorInterpolator.OnValueChanged = [this](SDL_Color color) {
        m_CurrentForegroundColor = color;
    };

    m_CurrentBorderColorInterpolator.OnValueChanged = [this](SDL_Color color) {
        m_CurrentBorderColor = color;
    };

    m_Font = Context.Turk->GetFontDescriptor("Inter-Variable", 16);
    SetText(text);

    SetAnimationState(Idle);
}

Controls::Button::~Button()
{
    SDL_DestroyTexture(m_TextTexture);
}

void Controls::Button::Update(double deltaTime)
{
    m_CurrentBackgroundColorInterpolator.Update(deltaTime);
    m_CurrentForegroundColorInterpolator.Update(deltaTime);
    m_CurrentBorderColorInterpolator.Update(deltaTime);
}

void Controls::Button::EventUpdate(SDL_Event &event)
{
    // Do not process any events if control is disabled
    if (Visibility == ControlVisibility::VisibleDisabled) 
        return;

    if (event.type == SDL_EVENT_MOUSE_MOTION || event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        SDL_Rect miceRect = SDL_Rect();
        miceRect.x = event.motion.x;
        miceRect.y = event.motion.y;
        miceRect.w = 1;
        miceRect.h = 1;

        SDL_Rect absoluteRect = SDL_Rect();
        absoluteRect.x = AbsolutePosition.x;
        absoluteRect.y = AbsolutePosition.y;
        absoluteRect.w = Size.x;
        absoluteRect.h = Size.y;

        if (SDL_HasRectIntersection(&absoluteRect, &miceRect))
        {
            TaiyouButtonState state = m_CurrentState;
            
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                state = TaiyouButtonState::Pressed;

            } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && m_CurrentState == TaiyouButtonState::Pressed)
            {
                state = TaiyouButtonState::Hovering;
                PerformClick();

            } else if (event.type == SDL_EVENT_MOUSE_MOTION && m_CurrentState == TaiyouButtonState::Idle) {
                state = TaiyouButtonState::Hovering;
            }

            SetAnimationState(state);
        } else {
            SetAnimationState(TaiyouButtonState::Idle);
        }
    }
}

void Controls::Button::SetText(const std::string& text)
{
    m_Text = text;

    // Free old text texture (if any)
    SDL_DestroyTexture(m_TextTexture);

    SDL_Color foregroundColor = SDL_Color();
    foregroundColor.r = 255;
    foregroundColor.g = 255;
    foregroundColor.b = 255;
    foregroundColor.a = 255;

    // Render UTF8 Blended font
    SDL_Surface *fontSurface = TTF_RenderText_Blended(Context.Turk->GetFont(m_Font), m_Text.c_str(), m_Text.size(), foregroundColor);

    m_TextTexture = SDL_CreateTextureFromSurface(Context.Renderer.get(), fontSurface);
    SDL_SetTextureBlendMode(m_TextTexture, SDL_BLENDMODE_BLEND);

    float sizeW, sizeH = 0;
    SDL_GetTextureSize(m_TextTexture, &sizeW, &sizeH);

    m_TextTextureSize.x = sizeW;
    m_TextTextureSize.y = sizeH;

    SDL_DestroySurface(fontSurface);

    MinimumSize.x = (Padding.x * 2) + m_TextTextureSize.x;
    MinimumSize.y = (Padding.y * 2) + m_TextTextureSize.y;
}

std::string Controls::Button::GetText() const
{
    return m_Text;
}

void Controls::Button::OnDraw(SDL_Renderer *renderer, double deltaTime)
{
    // Draw background rectangle
    SDL_SetRenderDrawColor(renderer, m_CurrentBorderColor.r, m_CurrentBorderColor.g, m_CurrentBorderColor.b, m_CurrentBorderColor.a);
    SDL_FRect size = SDL_FRect();
    size.x = 0;
    size.y = 0;
    size.w = Size.x;
    size.h = Size.y;
    SDL_RenderFillRect(renderer, &size);

    // Draw background border
    SDL_SetRenderDrawColor(renderer, m_CurrentBackgroundColor.r, m_CurrentBackgroundColor.g, m_CurrentBackgroundColor.b, m_CurrentBackgroundColor.a);
    size.x = 2;
    size.y = 2;
    size.w = Size.x - 4;
    size.h = Size.y - 4;
    SDL_RenderFillRect(renderer, &size);

    // Destination Rectangle for Text texture
    // Center Text texture inside control Size boundary
    SDL_FRect destRect = SDL_FRect();
    destRect.x = Size.x / 2.0 - m_TextTextureSize.x / 2.0;
    destRect.y = Size.y / 2.0 - m_TextTextureSize.y / 2.0;
    destRect.w = m_TextTextureSize.x;
    destRect.h = m_TextTextureSize.y;

    // Set foreground color
    SDL_SetTextureColorMod(m_TextTexture, m_CurrentForegroundColor.r, m_CurrentForegroundColor.g, m_CurrentForegroundColor.b);

    // Copy text texture to renderer
    SDL_RenderTexture(renderer, m_TextTexture, NULL, &destRect);
}

void Controls::Button::SetAnimationState(const TaiyouButtonState& newState)
{
    if (newState == m_CurrentState)
        return;
    
    m_LastState = m_CurrentState;
    m_CurrentState = newState;

    // Set start value to current value
    m_CurrentBackgroundColorInterpolator.SetStartValue(m_CurrentBackgroundColor);
    m_CurrentForegroundColorInterpolator.SetStartValue(m_CurrentForegroundColor);
    m_CurrentBorderColorInterpolator.SetStartValue(m_CurrentBorderColor);

    switch (newState)
    {
        case Controls::TaiyouButtonState::Idle : 
        {
            m_CurrentBackgroundColorInterpolator.SetTargetValue(s_ColorBackgroundIdle);
            m_CurrentForegroundColorInterpolator.SetTargetValue(s_ColorForegroundIdle);
            m_CurrentBorderColorInterpolator.SetTargetValue(s_ColorBorderIdle);
            break;
        }

        case Controls::TaiyouButtonState::Hovering : 
        {
            m_CurrentBackgroundColorInterpolator.SetTargetValue(s_ColorBackgroundHovering);
            m_CurrentForegroundColorInterpolator.SetTargetValue(s_ColorForegroundHovering);
            m_CurrentBorderColorInterpolator.SetTargetValue(s_ColorBorderHovering);
            break;
        }

        case Controls::TaiyouButtonState::Pressed : 
        {
            m_CurrentBackgroundColorInterpolator.SetTargetValue(s_ColorBackgroundPressed);
            m_CurrentForegroundColorInterpolator.SetTargetValue(s_ColorForegroundPressed);
            m_CurrentBorderColorInterpolator.SetTargetValue(s_ColorBorderPressed);
            break;
        }

        case Controls::TaiyouButtonState::Disabled : 
        {
            m_CurrentBackgroundColorInterpolator.SetTargetValue(s_ColorBackgroundDisabled);
            m_CurrentForegroundColorInterpolator.SetTargetValue(s_ColorForegroundDisabled);
            m_CurrentBorderColorInterpolator.SetTargetValue(s_ColorBorderDisabled);
            break;
        }
    }

    m_CurrentBackgroundColorInterpolator.Restart();
    m_CurrentForegroundColorInterpolator.Restart();
    m_CurrentBorderColorInterpolator.Restart();
}

void Controls::Button::PerformClick()
{
    if (!OnClick)
    {
        Context.Turk->LogWarning("Controls::Button; No callback registered for OnClick");
        return;
    }

    OnClick();
}