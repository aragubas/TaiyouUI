#include "Button.h"
#include <stdio.h>
using namespace TaiyouUI;


Controls::Button::Button(struct UIRootContext *context) : 
    m_Text(std::string()), m_TextTexture(nullptr)
{
    MinimumSize = SDL_FPoint();
    MinimumSize.x = 500;
    MinimumSize.y = 120;
    UIRootContext = context;

    // TODO: Replace with TURK
    m_Font = UIRootContext->Turk->GetFontDescriptor("Inter-Variable", 18);
}

Controls::Button::~Button()
{
    SDL_DestroyTexture(m_TextTexture);
}

void Controls::Button::EventUpdate(SDL_Event &event)
{
}

void Controls::Button::Update(double deltaTime)
{
}

void Controls::Button::OnDraw(SDL_Renderer *renderer, double deltaTime)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect size = SDL_Rect();
    size.x = 0;
    size.y = 0;
    size.w = Size.x;
    size.h = Size.y;
    SDL_RenderFillRect(renderer, &size);
}

void Controls::Button::SetText(std::string text)
{
    m_Text = text;

    // Free old text texture
    SDL_DestroyTexture(m_TextTexture);

    SDL_Color foregroundColor = SDL_Color();
    foregroundColor.a = 255;
    foregroundColor.r = 255;
    foregroundColor.g = 255;
    foregroundColor.b = 255;

    SDL_Color backgroundColor = SDL_Color();
    backgroundColor.a = 0;
    backgroundColor.r = 0;
    backgroundColor.g = 0;
    backgroundColor.b = 0;

    SDL_Surface *fontSurface = TTF_RenderText_LCD(UIRootContext->Turk->GetFont(m_Font), m_Text.c_str(), foregroundColor, backgroundColor);

    m_TextTexture = SDL_CreateTextureFromSurface(UIRootContext->Renderer, fontSurface);

    SDL_FreeSurface(fontSurface);
}

std::string Controls::Button::GetText() const
{
    return m_Text;
}