#include "Container.h"

void Container::BuildUI()
{
    // Check if there's at least one component
    if (Controls.size() == 0)
        return;

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
    Control *control = Controls[0];

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

void Container::EventUpdate(SDL_Event &event)
{
    if (Controls.size() == 0 || (Size.x == 0 || Size.y == 0))
        return;

    using LayersReverseIterator = std::vector<Control *>::const_reverse_iterator;

    for (LayersReverseIterator it = Controls.rbegin();
         it != Controls.rend(); it++)
    {
        it[0]->EventUpdate(event);
    }
}

void Container::AddControl(Control *control)
{
    control->ParentControl = this;
    Controls.push_back(control);
}

void Container::Update(double deltaTime)
{
    // Build the UI every frame
    BuildUI();

    // Don't do anything if there's any controls
    if (Controls.size() == 0)
        return;

    if (Type == ContainerType::Center)
    {
        Controls[0]->Update(deltaTime);
    }
    else
    {
        for (Control *control : Controls)
        {
            control->Update(deltaTime);
        }
    }
}

void Container::OnDraw(SDL_Renderer *renderer, double deltaTime)
{
    // Don't do anything if there's any controls
    if (Controls.size() == 0)
        return;

    if (Type == ContainerType::Center)
    {
        Controls[0]->Draw(renderer, deltaTime);
    }
    else
    {
        for (Control *control : Controls)
        {
            control->Draw(renderer, deltaTime);
        }
    }
}
