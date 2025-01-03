#include "Button.h"
#include "TaiyouUI/Control.h"
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <stdio.h>
#include <math.h>
using namespace TaiyouUI;


Controls::Button::Button(const UIRootContext& context, const std::string& text, Control* parentControl) :
    Control(context, parentControl), // Base Constructor
    m_Text(std::string()), TextTexture(nullptr),
    TextTextureSize(SDL_Point()), m_CurrentBackgroundColor(SDL_Color()),
    m_TargetBackgroundColor(SDL_Color()), m_CurrentForegroundColor(SDL_Color()),
    m_TargetForegroundColor(SDL_Color())
{
    Padding = SDL_FPoint();
    Padding.x = 12;
    Padding.y = 4;
    
    Font = Context.Turk->GetFontDescriptor("Inter-Variable", 16);
    SetText(text);
    SetAnimationState(Idle);
}

Controls::Button::~Button()
{
    SDL_DestroyTexture(TextTexture);
}

void Controls::Button::Update(double deltaTime)
{
    // Credit for Delta Time function
    // https://www.construct.net/en/blogs/ashleys-blog-2/using-lerp-delta-time-924
    // a = lerp(a, b, 1 - f ^ dt)
    // TODO: Make a function that interpolates between values based on time (t) factor
    float timeFunc = 1 - (pow(0.005, deltaTime));

    m_CurrentBackgroundColor.r = lerp(m_CurrentBackgroundColor.r, m_TargetBackgroundColor.r, timeFunc);
    m_CurrentBackgroundColor.g = lerp(m_CurrentBackgroundColor.g, m_TargetBackgroundColor.g, timeFunc);
    m_CurrentBackgroundColor.b = lerp(m_CurrentBackgroundColor.b, m_TargetBackgroundColor.b, timeFunc);

    m_CurrentBorderColor.r = lerp(m_CurrentBorderColor.r, m_TargetBorderColor.r, timeFunc);
    m_CurrentBorderColor.g = lerp(m_CurrentBorderColor.g, m_TargetBorderColor.g, timeFunc);
    m_CurrentBorderColor.b = lerp(m_CurrentBorderColor.b, m_TargetBorderColor.b, timeFunc);
}

void Controls::Button::EventUpdate(SDL_Event &event)
{
    // Do not process any events if control is disabled
    if (Visibility == ControlVisibility::VisibleDisabled) 
        return;

    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Rect miceRect = SDL_Rect();
        miceRect.x = event.motion.x;
        miceRect.y = event.motion.y;
        miceRect.w = 5;
        miceRect.h = 5;

        SDL_Rect absoluteRect = SDL_Rect();
        absoluteRect.x = AbsolutePosition.x;
        absoluteRect.y = AbsolutePosition.y;
        absoluteRect.w = Size.x;
        absoluteRect.h = Size.y;

        if (SDL_HasIntersection(&absoluteRect, &miceRect))
        {
            TaiyouButtonState state = TaiyouButtonState::Idle;

            if (event.type == SDL_MOUSEMOTION)
            {
                state = TaiyouButtonState::Hovering;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                state = TaiyouButtonState::Pressed;
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
    SDL_DestroyTexture(TextTexture);

    SDL_Color foregroundColor = SDL_Color();
    foregroundColor.a = 255;
    foregroundColor.r = 255;
    foregroundColor.g = 255;
    foregroundColor.b = 255;

    // Render UTF8 Blended font
    SDL_Surface *fontSurface = TTF_RenderUTF8_Blended(Context.Turk->GetFont(Font), m_Text.c_str(), foregroundColor);

    TextTexture = SDL_CreateTextureFromSurface(Context.Renderer, fontSurface);
    SDL_SetTextureBlendMode(TextTexture, SDL_BLENDMODE_BLEND);

    int sizeW, sizeH = 0;
    SDL_QueryTexture(TextTexture, NULL, NULL, &sizeW, &sizeH);

    TextTextureSize.x = sizeW;
    TextTextureSize.y = sizeH;

    SDL_FreeSurface(fontSurface);

    MinimumSize.x = (Padding.x * 2) + TextTextureSize.x;
    MinimumSize.y = (Padding.y * 2) + TextTextureSize.y;
}

std::string Controls::Button::GetText() const
{
    return m_Text;
}

void Controls::Button::OnDraw(SDL_Renderer *renderer, double deltaTime)
{
    // Draw background rectangle
    SDL_SetRenderDrawColor(renderer, m_CurrentBackgroundColor.r, m_CurrentBackgroundColor.g, m_CurrentBackgroundColor.b, m_CurrentBackgroundColor.a);
    SDL_Rect size = SDL_Rect();
    size.x = 0;
    size.y = 0;
    size.w = Size.x;
    size.h = Size.y;
    SDL_RenderFillRect(renderer, &size);

    // Draw background border
    SDL_SetRenderDrawColor(renderer, m_CurrentBorderColor.r, m_CurrentBorderColor.g, m_CurrentBorderColor.b, m_CurrentBorderColor.a);
    SDL_RenderDrawRect(renderer, &size);

    // Destination Rectangle for Text texture
    // Center Text texture inside control Size boundary
    SDL_Rect destRect = SDL_Rect();
    destRect.x = Size.x / 2.0 - TextTextureSize.x / 2.0;
    destRect.y = Size.y / 2.0 - TextTextureSize.y / 2.0;
    destRect.w = TextTextureSize.x;
    destRect.h = TextTextureSize.y;

    // Set foreground color
    SDL_SetTextureColorMod(TextTexture, m_CurrentForegroundColor.r, m_CurrentForegroundColor.g, m_CurrentForegroundColor.b);

    SDL_RenderCopy(renderer, TextTexture, NULL, &destRect);
}

void Controls::Button::SetAnimationState(const TaiyouButtonState newState)
{
    if (newState == m_CurrentState)
        return;
    
    m_LastState = m_CurrentState;
    m_CurrentState = newState;

    switch (newState)
    {
        case Controls::TaiyouButtonState::Idle : 
        {
            m_TargetBackgroundColor.r = 225;
            m_TargetBackgroundColor.g = 225;
            m_TargetBackgroundColor.b = 225;

            m_TargetForegroundColor.r = 50;
            m_TargetForegroundColor.g = 50;
            m_TargetForegroundColor.b = 50;

            m_TargetBorderColor.r = 173;
            m_TargetBorderColor.g = 173;
            m_TargetBorderColor.b = 173;
            break;
        }

        case Controls::TaiyouButtonState::Hovering : 
        {
            m_TargetBackgroundColor.r = 229;
            m_TargetBackgroundColor.g = 241;
            m_TargetBackgroundColor.b = 215;

            m_TargetForegroundColor.r = 45;
            m_TargetForegroundColor.g = 45;
            m_TargetForegroundColor.b = 45;

            m_TargetBorderColor.r = 0;
            m_TargetBorderColor.g = 120;
            m_TargetBorderColor.b = 215;
            break;
        }

        case Controls::TaiyouButtonState::Pressed : 
        {
            m_TargetBackgroundColor.r = 204;
            m_TargetBackgroundColor.g = 228;
            m_TargetBackgroundColor.b = 247;

            m_TargetForegroundColor.r = 5;
            m_TargetForegroundColor.g = 5;
            m_TargetForegroundColor.b = 5;
            break;
        }

        case Controls::TaiyouButtonState::Disabled : 
        {
            m_TargetBackgroundColor.r = 204;
            m_TargetBackgroundColor.g = 204;
            m_TargetBackgroundColor.b = 204;

            m_TargetForegroundColor.r = 135;
            m_TargetForegroundColor.g = 135;
            m_TargetForegroundColor.b = 135;
            break;
        }
    }
}