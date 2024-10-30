#include "Control.h"
#include <iostream>
using namespace TaiyouUI;


TaiyouUI::Control::Control() :
    UIRootContext(nullptr), RelativePosition(SDL_FPoint(0, 0)),
    AbsolutePosition(SDL_FPoint(0, 0)), MinimumSize(SDL_FPoint(0, 0)),
    MaximumSize(SDL_FPoint(0, 0)), Size(SDL_FPoint(0, 0)),
    IsVisible(true), IsEnabled(true),
    ParentControl(nullptr)
{
    std::cout << "Base constructor called" << std::endl;
}

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