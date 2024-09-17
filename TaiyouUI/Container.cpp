#include "Container.h"

void Container::BuildUI()
{
    // Check if there's at least one component
    if (Controls.size() == 0) return;

    switch (Type)
    {
    case ContainerType::Center:
        BuildCenter();
        break;

    case ContainerType::DockFill:
        BuildDockFill();
        break;

    case ContainerType::List:
        BuildList();
        break;
    
    default:
        break;
    }
}

void Container::BuildCenter()
{
    Control* control = Controls[0];
    
    // Constrain control to minimum size
    control->Size = control->MinimumSize;

    control->RelativePosition.x = Size.x / 2 - control->Size.x / 2;
    control->RelativePosition.y = Size.y / 2 - control->Size.y / 2;
}

// TODO: Implement DockFill
void Container::BuildDockFill()
{

}

// TODO: Implement List
void Container::BuildList()
{

}

Container::Container()
{

}

void Container::Update(double deltaTime)
{
    // Build the UI every frame
    BuildUI();
}

void Container::Draw(SDL_Renderer *renderer, double deltaTime)
{

}
