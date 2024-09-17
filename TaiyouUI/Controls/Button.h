#pragma once
#include <string>
#include "../Control.h"

class Button : public Control
{
    SDL_Rect backgroundRect;

public:
    std::string Text;
    
    Button();
    
    void Update(double deltaTime) override;
    void Draw(SDL_Renderer* renderer, double deltaTime) override;
};