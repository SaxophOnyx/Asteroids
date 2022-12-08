#include "LabeledCounter.h"

namespace ast
{
    LabeledCounter::LabeledCounter(RECT& borders, LPCSTR caption)
        : UIComponent(borders), caption(caption), count(0), prevCount(0)
    {
        captionLength = strlen(caption);
        initSubRects();

        countStr = std::to_string(count);
    }

    LabeledCounter::LabeledCounter(int x1, int y1, int x2, int y2, LPCSTR caption)
        : UIComponent(x1, y1, x2, y2), caption(caption), count(0), prevCount(0)
    {
        captionLength = strlen(caption);
        initSubRects();

        countStr = std::to_string(count);
    }

    LabeledCounter::~LabeledCounter()
    {

    }

    void LabeledCounter::update(int newCount)
    {
        if (count != newCount)
        {
            prevCount = count;
            count = newCount;

            countStr = std::to_string(count);
        }
    }

    void LabeledCounter::render(HDC hdc)
    {
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, backgroundBrush);
        HPEN oldPen = (HPEN)SelectObject(hdc, borderPen);
        HFONT oldFont = (HFONT)SelectObject(hdc, font);
        COLORREF oldTextColor = SetTextColor(hdc, textColor);

        Rectangle(hdc, boundaries.left, boundaries.top, boundaries.right, boundaries.bottom);
        DrawTextA(hdc, caption, captionLength, &captionRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        DrawTextA(hdc, ":", 1, &separatorRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        auto winStr = countStr.c_str();
        DrawTextA(hdc, winStr, countStr.length(), &countRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        SetTextColor(hdc, oldTextColor);
        SelectObject(hdc, font);
        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
    }

    void LabeledCounter::setBorderPen(HPEN& pen)
    {
        borderPen = pen;
    }

    void LabeledCounter::setBackgroundBrush(HBRUSH& brush)
    {
        backgroundBrush = brush;
    }

    void LabeledCounter::setFont(HFONT& font)
    {
        this->font = font;
    }

    void LabeledCounter::setTextColor(COLORREF& color)
    {
        textColor = color;
    }

    void LabeledCounter::initSubRects()
    {
        captionRect.left = boundaries.left;
        captionRect.top = boundaries.top;
        captionRect.right = boundaries.left + (boundaries.right - boundaries.left) * 0.6;
        captionRect.bottom = boundaries.bottom;

        countRect.left = boundaries.right - (boundaries.right - boundaries.left) * 0.35;
        countRect.right = boundaries.right;
        countRect.top = boundaries.top;
        countRect.bottom = boundaries.bottom;

        separatorRect.left = captionRect.right;
        separatorRect.right = countRect.left;
        separatorRect.top = boundaries.top;
        separatorRect.bottom = boundaries.bottom;
    }
}
