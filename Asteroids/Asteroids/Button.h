#pragma once

#include "UIComponent.h"

namespace ast
{
    enum ButtonState { IDLE = 0, HOVER, PRESSED };

    class Button : public UIComponent
    {
        public:
        Button(RECT& boundaries, LPCSTR caption);
        Button(int x1, int y1, int x2, int y2, LPCSTR caption);
        Button(Button&) = delete;
        virtual ~Button();

        void setBorderPen(HPEN& pen);
        void setFont(HFONT& font);
        void setIdleBackgroundBrush(HBRUSH& brush);
        void setHoverBackgroundBrush(HBRUSH& brush);
        void setPressedBackgroundBrush(HBRUSH& brush);
        void setTextColor(COLORREF& color);

        void update(double dt, POINT& mousePos);
        virtual void render(HDC hdc) override;
        bool isPressed();

        private:
        HPEN borderPen;
        HFONT font;
        HBRUSH idleBackground;
        HBRUSH hoverBackground;
        HBRUSH pressedBackground;
        COLORREF textColor;

        ButtonState state;
        LPCSTR caption;
        int captionLength;
        bool isTriggered;
    };
}
