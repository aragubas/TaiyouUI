#include "Control.h"

void Control::Draw(SDL_Renderer *renderer, double deltaTime)
{
    SDL_Rect oldViewport = SDL_Rect();
    SDL_RenderGetViewport(renderer, &oldViewport);

    // Set up new viewport
    SDL_Rect newViewport = SDL_Rect();
    newViewport.x = RelativePosition.x;
    newViewport.y = RelativePosition.y;
    newViewport.w = Size.x;
    newViewport.h = Size.y;
    SDL_RenderSetViewport(renderer, &newViewport);

    OnDraw(renderer, deltaTime);

    SDL_RenderSetViewport(renderer, &oldViewport);
}