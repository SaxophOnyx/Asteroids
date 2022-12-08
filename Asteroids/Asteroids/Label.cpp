#include "Label.h"

namespace ast
{
    Label::Label(RECT& borders, LPCSTR caption)
        : UIComponent(borders), caption(caption)
    {
        captionLength = strlen(caption);
    }

    Label::Label(int x1, int y1, int x2, int y2, LPCSTR caption)
        : UIComponent(x1, y1, x2, y2), caption(caption)
    {
        captionLength = strlen(caption);
    }

    Label::~Label()
    {

    }

    void Label::render(HDC hdc)
    {
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, backgroundBrush);
        HPEN oldPen = (HPEN)SelectObject(hdc, borderPen);
        HFONT oldFont = (HFONT)SelectObject(hdc, font);
        COLORREF oldColor = SetTextColor(hdc, textColor);

        Rectangle(hdc, boundaries.left, boundaries.top, boundaries.right, boundaries.bottom);
        DrawTextA(hdc, caption, captionLength, &boundaries, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        SetTextColor(hdc, oldColor);
        SelectObject(hdc, font);
        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
    }

    void Label::setBorderPen(HPEN& pen)
    {
        borderPen = pen;
    }

    void Label::setBackgroundBrush(HBRUSH& brush)
    {
        backgroundBrush = brush;
    }

    void Label::setFont(HFONT& font)
    {
        this->font = font;
    }

    void Label::setTextColor(COLORREF& color)
    {
        textColor = color;
    }
}
