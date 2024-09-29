#include "Button.h"
#include <stdio.h>

Button::Button(struct UIRootContext context) : m_Text(std::string()), m_TextTexture(nullptr)
{
    MinimumSize = SDL_FPoint();
    MinimumSize.x = 500;
    MinimumSize.y = 120;

    m_Font = TTF_OpenFont("./Application Data/Fonts/Inter-Variable.ttf", 20);
    if (m_Font == NULL)
    {
        throw "Default font not found";
    }
}

Button::~Button()
{
    SDL_DestroyTexture(m_TextTexture);
}

void Button::EventUpdate(SDL_Event &event)
{
}

void Button::Update(double deltaTime)
{
}

void Button::OnDraw(SDL_Renderer *renderer, double deltaTime)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect size = SDL_Rect();
    size.x = 0;
    size.y = 0;
    size.w = Size.x;
    size.h = Size.y;
    SDL_RenderFillRect(renderer, &size);
}

void Button::SetText(std::string text)
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

    SDL_Surface *fontSurface = TTF_RenderText_LCD(m_Font, m_Text.c_str(), foregroundColor, backgroundColor);

    // SDL_CreateTextureFromSurface()

    SDL_FreeSurface(fontSurface);
}

std::string Button::GetText() const
{
    return m_Text;
}