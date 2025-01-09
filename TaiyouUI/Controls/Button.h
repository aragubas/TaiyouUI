#pragma once
#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "../Control.h"
#include "../UIRootContext.h"
#include "TaiyouUI/Animation/ColorInterpolator.h"
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
        std::function<void()> OnClick;

        Button(const UIRootContext& context, const std::string& text, Control* parentControl = nullptr);
        ~Button();

        void Update(double deltaTime) override;
        void EventUpdate(SDL_Event &event) override;

        void SetText(const std::string& Text);
        std::string GetText() const;

    protected:
        void OnDraw(SDL_Renderer *renderer, double deltaTime) override;

    private:
        SDL_Texture *m_TextTexture;
        SDL_Point m_TextTextureSize;
        FontDescriptor m_Font;

        const static SDL_Color s_ColorBackgroundIdle;
        const static SDL_Color s_ColorBackgroundHovering;
        const static SDL_Color s_ColorBackgroundPressed;
        const static SDL_Color s_ColorBackgroundDisabled;

        const static SDL_Color s_ColorForegroundIdle;
        const static SDL_Color s_ColorForegroundHovering;
        const static SDL_Color s_ColorForegroundPressed;
        const static SDL_Color s_ColorForegroundDisabled;

        const static SDL_Color s_ColorBorderIdle;
        const static SDL_Color s_ColorBorderHovering;
        const static SDL_Color s_ColorBorderPressed;
        const static SDL_Color s_ColorBorderDisabled;

        SDL_Color m_CurrentBackgroundColor;
        Animation::ColorInterpolator m_CurrentBackgroundColorInterpolator;
        SDL_Color m_CurrentForegroundColor;
        Animation::ColorInterpolator m_CurrentForegroundColorInterpolator;
        SDL_Color m_CurrentBorderColor;
        Animation::ColorInterpolator m_CurrentBorderColorInterpolator;

        TaiyouButtonState m_CurrentState;
        TaiyouButtonState m_LastState;
        std::string m_Text;

        void SetAnimationState(const TaiyouButtonState& newState);
        void PerformClick();
    };
}