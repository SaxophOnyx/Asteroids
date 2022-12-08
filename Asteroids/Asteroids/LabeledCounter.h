#pragma once

#include "UIComponent.h"
#include <string>

namespace ast
{
    class LabeledCounter : UIComponent
    {
        public:
        LabeledCounter(RECT& borders, LPCSTR caption);
        LabeledCounter(int x1, int y1, int x2, int y2, LPCSTR caption);
        LabeledCounter(LabeledCounter&) = delete;
        virtual ~LabeledCounter();

        void update(int newCount);
        virtual void render(HDC hdc) override;

        void setBorderPen(HPEN& pen);
        void setBackgroundBrush(HBRUSH& brush);
        void setFont(HFONT& font);
        void setTextColor(COLORREF& color);

        private:
        int count;
        int prevCount;

        LPCSTR caption;
        int captionLength;
        std::string countStr;

        RECT captionRect;
        RECT separatorRect;
        RECT countRect;

        HPEN borderPen;
        HBRUSH backgroundBrush;
        HFONT font;
        COLORREF textColor;

        void initSubRects();
    };
}
