#include "Button.h"

namespace ast
{
    Button::Button(RECT& boundaries, LPCSTR caption)
        : UIComponent(boundaries), caption(caption), state(IDLE), isTriggered(false)
    {
        captionLength = strlen(caption);
    }

    Button::Button(int x1, int y1, int x2, int y2, LPCSTR caption)
        : UIComponent(x1, y1, x2, y2), caption(caption), state(IDLE), isTriggered(false)
    {
        captionLength = strlen(caption);
    }

    Button::~Button()
    {

    }

    void Button::setBorderPen(HPEN& pen)
    {
        borderPen = pen;
    }

    void Button::setFont(HFONT& font)
    {
        this->font = font;
    }

    void Button::setIdleBackgroundBrush(HBRUSH& brush)
    {
        idleBackground = brush;
    }

    void Button::setHoverBackgroundBrush(HBRUSH& brush)
    {
        hoverBackground = brush;
    }

    void Button::setPressedBackgroundBrush(HBRUSH& brush)
    {
        pressedBackground = brush;
    }

    void Button::setTextColor(COLORREF& color)
    {
        textColor = color;
    }

    void Button::update(double dt, POINT& mousePos)
    {
        if (this->contains(mousePos))
        {
            short mouse = GetKeyState(VK_LBUTTON);
            if (mouse < 0)
            {
                if (this->state == HOVER)
                {
                    this->state = PRESSED;
                }
            }
            else
            {
                if (this->state == PRESSED)
                    this->isTriggered = true;
                else
                    this->isTriggered = false;

                this->state = HOVER;
            }
        }
        else
        {
            this->state = IDLE;
            this->isTriggered = false;
        }

    }

    void Button::render(HDC hdc)
    {
        HFONT oldFont = (HFONT)SelectObject(hdc, font);
        HPEN oldPen = (HPEN)SelectObject(hdc, borderPen);
        COLORREF oldTextColor = SetTextColor(hdc, textColor);
        HBRUSH oldBrush{};

        switch (state)
        {
            case ast::HOVER:
                oldBrush = (HBRUSH)SelectObject(hdc, hoverBackground);
                break;

            case ast::PRESSED:
                oldBrush = (HBRUSH)SelectObject(hdc, pressedBackground);
                break;

            default:
                oldBrush = (HBRUSH)SelectObject(hdc, idleBackground);
                break;
        }

        Rectangle(hdc, boundaries.left, boundaries.top, boundaries.right, boundaries.bottom);
        DrawTextA(hdc, caption, captionLength, &boundaries, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        SetTextColor(hdc, oldTextColor);
        SelectObject(hdc, oldBrush);
        SelectObject(hdc, oldPen);
        SelectObject(hdc, font);
    }

    bool Button::isPressed()
    {
        return isTriggered;
    }
}
