#include "Button.h"
#include "TaiyouUI/Control.h"
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <stdio.h>
using namespace TaiyouUI;


Controls::Button::Button(const UIRootContext& context, const std::string& text, Control* parentControl) :
    Control(context, parentControl), // Base Constructor
    m_Text(std::string()), TextTexture(nullptr),
    TextTextureSize(SDL_Point()), m_CurrentState(TaiyouButtonState::Idle),
    m_LastState(TaiyouButtonState::Idle)
{
    Padding = SDL_FPoint();
    Padding.x = 16;
    Padding.y = 8;
    
    Font = Context.Turk->GetFontDescriptor("Inter-Variable", 24);
    SetText(text);
}

Controls::Button::~Button()
{
    SDL_DestroyTexture(TextTexture);
}

void Controls::Button::Update(double deltaTime)
{
    MinimumSize.x = TextTextureSize.x + 12;
    MinimumSize.y = TextTextureSize.y + 8;    
}

void Controls::Button::EventUpdate(SDL_Event &event)
{
    if (event.type == SDL_EventType::SDL_MOUSEMOTION)
    {
        SDL_Rect miceRect = SDL_Rect();
        miceRect.x = event.motion.x;
        miceRect.y = event.motion.y;
        miceRect.w = 1;
        miceRect.h = 1;

        SDL_Rect absoluteRect = SDL_Rect();
        absoluteRect.x = AbsolutePosition.x;
        absoluteRect.y = AbsolutePosition.y;
        miceRect.w = Size.x;
        miceRect.h = Size.y;

        if (SDL_HasIntersection(&absoluteRect, &miceRect))
        {
            SetAnimationState(TaiyouButtonState::Hovering);
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
    SDL_SetRenderDrawColor(renderer, m_CurrentBackgroundColor.r, m_CurrentBackgroundColor.g, m_CurrentBackgroundColor.b, m_CurrentBackgroundColor.a);
    SDL_Rect size = SDL_Rect();
    size.x = 0;
    size.y = 0;
    size.w = Size.x;
    size.h = Size.y;
    SDL_RenderFillRect(renderer, &size);
    
    SDL_Rect destRect = SDL_Rect();
    destRect.x = Size.x / 2.0 - TextTextureSize.x / 2.0;
    destRect.y = Size.y / 2.0 - TextTextureSize.y / 2.0;
    destRect.w = TextTextureSize.x;
    destRect.h = TextTextureSize.y;

    SDL_RenderCopy(renderer, TextTexture, NULL, &destRect);
}

void Controls::Button::SetAnimationState(const TaiyouButtonState newState)
{
    
}