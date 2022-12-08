#include "GameOverState.h"

namespace ast
{
    GameOverState::GameOverState(ISimpleResourceManager& resourceManager, RECT& windowBorders, long score, long time)
        : State(resourceManager, windowBorders), score(score), time(time)
    {
        initGui();
        background = resourceManager.getImage("gameover_background");
    }

    GameOverState::~GameOverState()
    {
        delete(exitButton);
        delete(gameOverLabel);
        delete(scoreCounter);
        delete(timeCounter);
    }

    void GameOverState::update(double dt, POINT& mousePos)
    {
        exitButton->update(dt, mousePos);
        if (exitButton->isPressed())
        {
            die();
            return;
        }

        scoreCounter->update(score);
        timeCounter->update(time);
    }

    void GameOverState::render(HDC hdc)
    {
        renderBackground(hdc);
        gameOverLabel->render(hdc);
        exitButton->render(hdc);
        scoreCounter->render(hdc);
        timeCounter->render(hdc);
    }

    void GameOverState::renderBackground(HDC hdc)
    {
        LONG topLeftX = windowBorders.left;
        LONG topLeftY = windowBorders.top;
        LONG bottomRightX = windowBorders.right;
        LONG bottomRightY = windowBorders.bottom;

        HDC bitmapDC = CreateCompatibleDC(hdc);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(bitmapDC, background);
        BitBlt(hdc, topLeftX, topLeftY, bottomRightX, bottomRightY, bitmapDC, 0, 0, SRCCOPY);
        SelectObject(bitmapDC, oldBitmap);
        DeleteObject(bitmapDC);
    }

    void GameOverState::initGui()
    {
        HFONT buttonFont = resourceManager.getFont("gameoverstate_gui_buttonFont");
        HFONT largeFont = resourceManager.getFont("default_large_font");
        HFONT headerFont = resourceManager.getFont("default_header_font");
        HPEN pen = resourceManager.getPen("default_gui_pen");
        HPEN emptyPen = resourceManager.getPen("empty_pen");
        HBRUSH transparent = resourceManager.getBrush("transparent_brush");
        HBRUSH idle = resourceManager.getBrush("default_gui_background");
        HBRUSH hover = resourceManager.getBrush("button_hover_background");
        HBRUSH pressed = resourceManager.getBrush("button_pressed_background");
        COLORREF color = resourceManager.getColor("default_gui_text_color");

        int offset = 40;

        int labelWidth = 500;
        int labelHeight = 150;
        int labelLeft = windowBorders.left + (windowBorders.right - windowBorders.left - labelWidth) / 2;
        int labelTop = offset;

        gameOverLabel = new Label(labelLeft, labelTop , labelLeft + labelWidth, labelTop + labelHeight, "Game Over");
        gameOverLabel->setBorderPen(emptyPen);
        gameOverLabel->setBackgroundBrush(transparent);
        gameOverLabel->setFont(headerFont);
        gameOverLabel->setTextColor(color);

        int scoreWidth = 450;
        int scoreHeight = 70;
        int scoreLeft = windowBorders.left + (windowBorders.right - windowBorders.left - scoreWidth) / 2;
        int scoreTop = labelTop + labelHeight + offset;

        scoreCounter = new LabeledCounter(scoreLeft, scoreTop, scoreLeft + scoreWidth, scoreTop + scoreHeight, "Score");
        scoreCounter->setBackgroundBrush(transparent);
        scoreCounter->setBorderPen(emptyPen);
        scoreCounter->setTextColor(color);
        scoreCounter->setFont(largeFont);

        int timeWidth = 450;
        int timeHeight = 70;
        int timeLeft = windowBorders.left + (windowBorders.right - windowBorders.left - timeWidth) / 2;
        int timeTop = scoreTop + scoreHeight + offset;

        timeCounter = new LabeledCounter(timeLeft, timeTop, timeLeft + timeWidth, timeTop + timeHeight, "Time");
        timeCounter->setBackgroundBrush(transparent);
        timeCounter->setBorderPen(emptyPen);
        timeCounter->setTextColor(color);
        timeCounter->setFont(largeFont);

        int exitWidth = 300;
        int exitHeight = 120;
        int exitLeft = windowBorders.left + (windowBorders.right - windowBorders.left - exitWidth) / 2;
        int exitTop = timeTop + timeHeight + offset * 2;

        exitButton = new Button(exitLeft, exitTop, exitLeft + exitWidth, exitTop + exitHeight, "To Main Menu");
        exitButton->setBorderPen(pen);
        exitButton->setFont(buttonFont);
        exitButton->setIdleBackgroundBrush(idle);
        exitButton->setHoverBackgroundBrush(hover);
        exitButton->setPressedBackgroundBrush(pressed);
        exitButton->setTextColor(color);
    }
}
