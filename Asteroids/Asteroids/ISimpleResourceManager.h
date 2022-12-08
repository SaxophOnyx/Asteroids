#pragma once

#include <windows.h>
#include <string>

namespace ast
{
    class ISimpleResourceManager
    {
        public:
        virtual HBITMAP& getImage(const std::string& key) = 0;
        virtual void loadImage(const std::string& key, const std::string& path) = 0;

        virtual HPEN getPen(const std::string& key) = 0;
        virtual void loadPen(const std::string& key, HPEN pen) = 0;

        virtual HBRUSH getBrush(const std::string& key) = 0;
        virtual void loadBrush(const std::string& key, HBRUSH brush) = 0;

        virtual HFONT getFont(const std::string& key) = 0;
        virtual void loadFont(const std::string& key, HFONT font) = 0;

        virtual COLORREF getColor(const std::string& key) = 0;
        virtual void loadColor(const std::string& key, COLORREF color) = 0;
    };
}
