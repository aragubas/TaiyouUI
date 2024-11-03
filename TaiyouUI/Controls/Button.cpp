#include "Button.h"
#include <stdio.h>
using namespace TaiyouUI;


Controls::Button::Button(struct UIRootContext *context) : 
    m_Text(std::string()), m_TextTexture(nullptr),
    m_TextTextureSize(SDL_Point())
{
    MinimumSize = SDL_FPoint();
    MinimumSize.x = 500;
    MinimumSize.y = 120;
    UIRootContext = context;

    // TODO: Replace with TURK
    m_Font = UIRootContext->Turk->GetFontDescriptor("Inter-Variable", 24);
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
    MinimumSize.x = m_TextTextureSize.x + 12;
    MinimumSize.y = m_TextTextureSize.y + 8;
}

void Controls::Button::OnDraw(SDL_Renderer *renderer, double deltaTime)
{
    SDL_SetRenderDrawColor(renderer, 32, 145, 5, 255);
    SDL_Rect size = SDL_Rect();
    size.x = 0;
    size.y = 0;
    size.w = Size.x;
    size.h = Size.y;
    SDL_RenderFillRect(renderer, &size);
    
    SDL_Rect destRect = SDL_Rect();
    destRect.x = Size.x / 2 - m_TextTextureSize.x / 2;
    destRect.y = Size.y / 2 - m_TextTextureSize.y / 2;
    destRect.w = m_TextTextureSize.x;
    destRect.h = m_TextTextureSize.y;

    SDL_RenderCopy(renderer, m_TextTexture, NULL, &destRect);
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
    backgroundColor.r = 255;
    backgroundColor.g = 255;
    backgroundColor.b = 255;

    SDL_Surface *fontSurface = TTF_RenderUTF8_Blended(UIRootContext->Turk->GetFont(m_Font), m_Text.c_str(), foregroundColor);

    m_TextTexture = SDL_CreateTextureFromSurface(UIRootContext->Renderer, fontSurface);
    SDL_SetTextureBlendMode(m_TextTexture, SDL_BLENDMODE_BLEND);

    int sizeW, sizeH = 0;
    SDL_QueryTexture(m_TextTexture, NULL, NULL, &sizeW, &sizeH);

    m_TextTextureSize.x = sizeW;
    m_TextTextureSize.y = sizeH;

    SDL_FreeSurface(fontSurface);
}

std::string Controls::Button::GetText() const
{
    return m_Text;
}