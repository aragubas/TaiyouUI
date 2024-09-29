#pragma once
#include <vector>
#include "Control.h"

enum ContainerType
{
    Center,
    DockFill,
    List
};

class Container : public Control
{
    /// @brief Called when the UI needs to be re-built. Usually after resizing/adding component
    void BuildUI();
    void BuildCenter();
    void BuildDockFill();
    void BuildList();

public:
    std::vector<Control *> Controls;
    ContainerType Type;

    Container();

    void Update(double deltaTime) override;
    void EventUpdate(SDL_Event &event) override;
    void AddControl(Control *control);

private:
    void OnDraw(SDL_Renderer *renderer, double deltaTime) override;
};