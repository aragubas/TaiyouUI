#include "UIRoot.h"
#include "InputEvent.h"

UIRoot::UIRoot() : m_Layers(std::vector<Layer *>())
{
    Size = SDL_Point();
    Size.x = 0;
    Size.y = 0;
}

Layer *UIRoot::CreateLayer(Container *container)
{
    unsigned int index = m_Layers.size() + 1;
    Layer *layer = new Layer(index);

    layer->RootContainer = container;

    m_Layers.push_back(layer);

    return layer;
}

void UIRoot::RemoveLayer(unsigned int index)
{
    m_Layers.erase(m_Layers.begin() + index);
}

void UIRoot::Update(double deltaTime)
{
    // Update every component from back to front
    for (Layer *layer : m_Layers)
    {
        // Set RootContainer size to current size
        layer->RootContainer->Size.x = Size.x;
        layer->RootContainer->Size.y = Size.y;

        layer->RootContainer->Update(deltaTime);
    }
}

void UIRoot::Draw(SDL_Renderer *renderer, double deltaTime)
{
    // Do not draw anything if any of the size dimensions is 0
    if (Size.x == 0 || Size.y == 0)
        return;

    // Draw every layer from back to front
    for (Layer *layer : m_Layers)
    {
        layer->RootContainer->Draw(renderer, deltaTime);
    }
}

void UIRoot::EventUpdate(SDL_Event event)
{
}