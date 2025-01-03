#pragma once
#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "../Control.h"
#include "../UIRootContext.h"
#include <TaiyouUI/Turk/FontDescriptor.h>
using namespace TaiyouUI::Turk;


namespace TaiyouUI::Controls
{
    enum TaiyouButtonState : char
    {
        Idle,
        Hovering,
        Pressed,
        Disabled
    };

    class Button : public Control
    {
    public:
        void (*OnClick) ();

        Button(const UIRootContext& context, const std::string& text, Control* parentControl = nullptr);
        ~Button();

        void Update(double deltaTime) override;
        void EventUpdate(SDL_Event &event) override;

        void SetText(const std::string& Text);
        std::string GetText() const;

    private:
        SDL_Texture *m_TextTexture;
        SDL_Point m_TextTextureSize;
        FontDescriptor m_Font;

        SDL_Color m_CurrentBackgroundColor;
        SDL_Color m_CurrentForegroundColor;
        SDL_Color m_TargetBackgroundColor;
        SDL_Color m_TargetForegroundColor;
        SDL_Color m_CurrentBorderColor;
        SDL_Color m_TargetBorderColor;

        TaiyouButtonState m_CurrentState;
        TaiyouButtonState m_LastState;
        std::string m_Text;

        void OnDraw(SDL_Renderer *renderer, double deltaTime) override;
        void SetAnimationState(const TaiyouButtonState& newState);
        void PerformClick();
    };
}