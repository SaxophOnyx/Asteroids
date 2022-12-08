#include "MainMenuState.h"
#include "GameState.h"

namespace ast
{
    MainMenuState::MainMenuState(ISimpleResourceManager& resourceManager, RECT& windowBorders)
        : State(resourceManager, windowBorders)
    {
        background = resourceManager.getImage("mainmenustate_background");
        initGui();
    }

    MainMenuState::~MainMenuState()
    {
        delete(newGameButton);
        delete(exitButton);
        delete(header);
    }

    void MainMenuState::update(double dt, POINT& mousePos)
    {
        newGameButton->update(dt, mousePos);
        if (newGameButton->isPressed())
        {
            GameState* state = new GameState(resourceManager, windowBorders);
            setNewState(state);
            return;
        }

        exitButton->update(dt, mousePos);
        if (exitButton->isPressed())
        {
            die();
            return;
        }
    }

    void MainMenuState::render(HDC hdc)
    {
        renderBackground(hdc);
        header->render(hdc);
        newGameButton->render(hdc);
        exitButton->render(hdc);
    }

    void MainMenuState::initGui()
    {
        HFONT font = resourceManager.getFont("mainmenustate_gui_font");
        HFONT headerFont = resourceManager.getFont("default_header_font");
        HPEN pen = resourceManager.getPen("default_gui_pen");
        HPEN emptyPen = resourceManager.getPen("empty_pen");
        HBRUSH transparent = resourceManager.getBrush("transparent_brush");
        HBRUSH idle = resourceManager.getBrush("default_gui_background");
        HBRUSH hover = resourceManager.getBrush("button_hover_background");
        HBRUSH pressed = resourceManager.getBrush("button_pressed_background");
        COLORREF color = resourceManager.getColor("default_gui_text_color");

        int offset = 40;

        int headerWidth = 500;
        int headerHeight = 200;
        int headerLeft = windowBorders.left + (windowBorders.right - windowBorders.left - headerWidth) / 2;
        int headerTop = windowBorders.top + offset;
        header = new Label(headerLeft, headerTop, headerLeft + headerWidth, headerTop + headerHeight, "Asteroids!");
        header->setFont(headerFont);
        header->setTextColor(color);
        header->setBackgroundBrush(transparent);
        header->setBorderPen(emptyPen);

        int newGameWidth = 250;
        int newGameHeight = 120;
        int newGameLeft = windowBorders.left + (windowBorders.right - windowBorders.left - newGameWidth) / 2;
        int newGameTop = headerTop + headerHeight + offset;

        newGameButton = new Button(newGameLeft, newGameTop, newGameLeft + newGameWidth, newGameTop + newGameHeight, "New Game");
        newGameButton->setBorderPen(pen);
        newGameButton->setFont(font);
        newGameButton->setIdleBackgroundBrush(idle);
        newGameButton->setHoverBackgroundBrush(hover);
        newGameButton->setPressedBackgroundBrush(pressed);
        newGameButton->setTextColor(color);

        int exitWidth = 250;
        int exitHeight = 120;
        int exitLeft = windowBorders.left + (windowBorders.right - windowBorders.left - exitWidth) / 2;
        int exitTop = newGameTop + newGameHeight + offset;

        exitButton = new Button(exitLeft, exitTop, exitLeft + exitWidth, exitTop + exitHeight, "Exit");
        exitButton->setBorderPen(pen);
        exitButton->setFont(font);
        exitButton->setIdleBackgroundBrush(idle);
        exitButton->setHoverBackgroundBrush(hover);
        exitButton->setPressedBackgroundBrush(pressed);
        exitButton->setTextColor(color);
    }

    void MainMenuState::renderBackground(HDC hdc)
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
}
