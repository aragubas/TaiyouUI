#include "Button.h"
#include <stdio.h>

Button::Button()
{
    backgroundRect = SDL_Rect();
    MinimumSize = SDL_FPoint();
    MinimumSize.x = 500;
    MinimumSize.y = 120;
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
