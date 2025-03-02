#include "Control.h"
#include "TaiyouUI/UIRootContext.h"
#include <SDL3/SDL_rect.h>
using namespace TaiyouUI;


Control::Control(const UIRootContext& context, Control* parentControl) :
    Context(context), ParentControl(parentControl), 
    RelativePosition(SDL_FPoint(0, 0)), AbsolutePosition(SDL_FPoint(0, 0)), 
    MinimumSize(SDL_FPoint(0, 0)), MaximumSize(SDL_FPoint(0, 0)), 
    Padding(SDL_FPoint(0, 0)), Size(SDL_FPoint(0, 0)), 
    Visibility(ControlVisibility::VisibleEnabled)
{
    // TODO: Add initialization logic for controls
}

void Control::Draw(SDL_Renderer *renderer, double deltaTime)
{
    // Don't render anything if the control is meant to be invisible
    if (Visibility == ControlVisibility::Invisible) return;

    SDL_Rect oldViewport = SDL_Rect();
    SDL_GetRenderViewport(renderer, &oldViewport);
    

    // Set up new viewport
    SDL_Rect newViewport = SDL_Rect();
    newViewport.x = RelativePosition.x;
    newViewport.y = RelativePosition.y;
    newViewport.w = Size.x;
    newViewport.h = Size.y;
    SDL_SetRenderViewport(renderer, &newViewport);

    OnDraw(renderer, deltaTime);

    SDL_SetRenderViewport(renderer, &oldViewport);
}