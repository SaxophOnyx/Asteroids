#pragma once

#include "UIComponent.h"

namespace ast
{
    class Label : public UIComponent
    {
        public:
        Label(RECT& borders, LPCSTR caption);
        Label(int x1, int y1, int x2, int y2, LPCSTR caption);
        Label(Label&) = delete;
        virtual ~Label();

        virtual void render(HDC hdc) override;

        void setBorderPen(HPEN& pen);
        void setBackgroundBrush(HBRUSH& brush);
        void setFont(HFONT& font);
        void setTextColor(COLORREF& color);

        private:
        LPCSTR caption;
        int captionLength;

        HPEN borderPen;
        HBRUSH backgroundBrush;
        HFONT font;
        COLORREF textColor;
    };
}
