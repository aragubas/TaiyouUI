#pragma once
#include <string>
#include <SDL2/SDL_ttf.h>
#include "../Control.h"

class Button : public Control
{
    SDL_Rect backgroundRect;

public:
    std::string Text;

    Button();

    void Update(double deltaTime) override;

private:
    void OnDraw(SDL_Renderer *renderer, double deltaTime) override;
};