#pragma once

#include <windows.h>

namespace ast
{
    class UIComponent
    {
        public:
        UIComponent(UIComponent&) = delete;
        virtual ~UIComponent() = default;

        virtual void render(HDC hdc) = 0;
        bool contains(POINT& p);

        protected:
        UIComponent(RECT& boundaries);
        UIComponent(int x1, int y1, int x2, int y2);

        RECT boundaries;
    };
}
