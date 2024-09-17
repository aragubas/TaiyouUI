#pragma once
#include <vector>
#include "Control.h"

enum ContainerType {
    Center, DockFill, List
};

class Container : public Control
{
    /// @brief Called when the UI needs to be re-built. Usually after resizing/adding component
    void BuildUI();
    void BuildCenter();
    void BuildDockFill();
    void BuildList();

public:    
    std::vector<Control*> Controls;
    ContainerType Type;

    Container();

    void Update(double deltaTime);
    void Draw(SDL_Renderer* renderer, double deltaTime);
};