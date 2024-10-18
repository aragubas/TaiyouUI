#pragma once
#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "../Control.h"
#include "../UIRootContext.h"

class Button : public Control
{
    SDL_Texture *m_TextTexture;
    TTF_Font *m_Font;
    std::string m_Text;

public:
    Button(struct UIRootContext *context);
    ~Button();

    void Update(double deltaTime) override;
    void EventUpdate(SDL_Event &event) override;

    void SetText(std::string Text);
    std::string GetText() const;

private:
    void OnDraw(SDL_Renderer *renderer, double deltaTime) override;
};