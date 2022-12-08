#pragma once

#include "State.h"
#include "Button.h"
#include "Label.h"

namespace ast
{
    class MainMenuState : public State
    {
        public:
        MainMenuState(ISimpleResourceManager& resourceManager, RECT& windowBorders);
        MainMenuState(MainMenuState&) = delete;
        virtual ~MainMenuState();

        virtual void update(double dt, POINT& mousePos) override;
        virtual void render(HDC hdc) override;

        private:
        HBITMAP background;
        Button* newGameButton;
        Button* exitButton;
        Label* header;

        void initGui();
        void renderBackground(HDC hdc);
    };
}
