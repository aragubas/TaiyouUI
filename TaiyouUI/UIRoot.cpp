#include "UIRoot.h"
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <limits.h>
#include <limits>
using namespace TaiyouUI;


UIRoot::UIRoot(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Window> window) :
    m_Layers(std::vector<Layer>()), Turk(std::make_shared<TurkInstance>(renderer, window)) {
    Size = SDL_Point();
    Size.x = 0;
    Size.y = 0;

    Context = UIRootContext();
    Context.Renderer = renderer;
    Context.Window = window;
    Context.Turk = Turk;
}

uint UIRoot::CreateLayer(Container* container) {
    // Source: https://cplusplus.com/reference/cstdlib/rand/
    // Generate a random number for ID
    srand(time(NULL));
    unsigned int index = rand() % std::numeric_limits<uint>().max();

    m_Layers.emplace_back(index, container);

    return index;
}

void UIRoot::RemoveLayer(unsigned int id) {
    // Find layer index
    uint foundIndex = 0;
    for (uint i = 0; i < m_Layers.size(); i++)
    {
        if (m_Layers[i].Id == id)
        {
            foundIndex = i;
            break;
        }
    }

    // Deletes Root container
    delete m_Layers[foundIndex].RootContainer;

    m_Layers.erase(m_Layers.begin() + foundIndex);
}

void UIRoot::ClearLayers() {
    // Deletes every root container
    for (Layer layer : m_Layers)
    {
        Container* container = layer.RootContainer;
        if (container != nullptr)
            delete container;
    }

    m_Layers.clear();
}

void UIRoot::Update(double deltaTime) {
    // Update every component from back to front
    for (Layer layer : m_Layers)
    {
        // Set RootContainer size to current size
        layer.RootContainer->Size.x = Size.x;
        layer.RootContainer->Size.y = Size.y;

        layer.RootContainer->Update(deltaTime);
    }
}

void UIRoot::Draw(SDL_Renderer* renderer, double deltaTime) {
    // Do not draw anything if any of the size dimensions is 0
    if (Size.x == 0 || Size.y == 0)
        return;

    // Draw every layer from back to front
    for (Layer layer : m_Layers)
    {
        layer.RootContainer->Draw(renderer, deltaTime);
    }
}

void UIRoot::EventUpdate(SDL_Event& event) {
    using LayersReverseIterator = std::vector<Layer>::const_reverse_iterator;

    for (LayersReverseIterator it = m_Layers.rbegin();
         it != m_Layers.rend(); it++)
    {
        it[0].RootContainer->EventUpdate(event);
    }
}