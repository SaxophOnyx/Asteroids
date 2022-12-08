#include "UIComponent.h"

namespace ast
{
    UIComponent::UIComponent(RECT& boundaries)
    {
        this->boundaries.left = boundaries.left;
        this->boundaries.right = boundaries.right;
        this->boundaries.top = boundaries.top;
        this->boundaries.bottom = boundaries.bottom;
    }

    UIComponent::UIComponent(int x1, int y1, int x2, int y2)
    {
        this->boundaries.left = x1;
        this->boundaries.top = y1;
        this->boundaries.right = x2;
        this->boundaries.bottom = y2;
    }

    bool UIComponent::contains(POINT& p)
    {
        return !(p.x < this->boundaries.left
            || p.x > this->boundaries.right
            || p.y < this->boundaries.top
            || p.y > this->boundaries.bottom);
    }
}
