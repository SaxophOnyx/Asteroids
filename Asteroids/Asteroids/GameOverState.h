#pragma once

#include "State.h"
#include "Label.h"
#include "Button.h"
#include "LabeledCounter.h"

namespace ast
{
    class GameOverState : public State
    {
        public:
        GameOverState(ISimpleResourceManager& resourceManager, RECT& windowBorders, long score, long time);
        GameOverState(GameOverState&) = delete;
        virtual ~GameOverState();

        virtual void update(double dt, POINT& mousePos) override;
        virtual void render(HDC hdc) override;

        private:
        HBITMAP background;
        Label* gameOverLabel;
        Button* exitButton;
        LabeledCounter* scoreCounter;
        LabeledCounter* timeCounter;
        long score;
        long time;

        void renderBackground(HDC hdc);
        void initGui();
    };
}
