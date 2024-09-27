#include "UIRoot.h"
#include "InputEvent.h"

UIRoot::UIRoot() : m_Layers(std::vector<Layer *>())
{
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
    for (Layer *layer : m_Layers)
    {
        layer->RootContainer->Update(deltaTime);
    }
}

void UIRoot::Draw(SDL_Renderer *renderer, double deltaTime)
{
    for (Layer *layer : m_Layers)
    {
        layer->RootContainer->Draw(renderer, deltaTime);
    }
}

void UIRoot::EventUpdate(SDL_Event event)
{
}