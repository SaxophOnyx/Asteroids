#include "SimpleResourceManager.h"

namespace ast
{
    SimpleResourceManager::SimpleResourceManager(std::string folderPath)
    {
        this->folderPath = folderPath;
        this->folderPath += "\\";
    }

    SimpleResourceManager::~SimpleResourceManager()
    {
        for (auto& iter : images)
            DeleteObject(iter.second);

        for (auto& iter : pens)
            DeleteObject(iter.second);

        for (auto& iter : brushes)
            DeleteObject(iter.second);

        for (auto& iter : fonts)
            DeleteObject(iter.second);

        images.clear();
        pens.clear();
        brushes.clear();
        fonts.clear();
        colors.clear();
    }

    HBITMAP& SimpleResourceManager::getImage(const std::string& key)
    {
        HBITMAP result = images.at(key);
        return result;
    }

    void SimpleResourceManager::loadImage(const std::string& key, const std::string& path)
    {
        std::string fullPath = folderPath;
        fullPath += path;
        LPCSTR convertedPath = fullPath.c_str();

        HBITMAP image = (HBITMAP)LoadImageA(NULL, convertedPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        images.emplace(std::make_pair(key, image));
    }

    HPEN SimpleResourceManager::getPen(const std::string& key)
    {
        HPEN result = pens.at(key);
        return result;
    }

    void SimpleResourceManager::loadPen(const std::string& key, HPEN pen)
    {
        pens.emplace(std::make_pair(key, pen));
    }

    HBRUSH SimpleResourceManager::getBrush(const std::string& key)
    {
        HBRUSH result = brushes.at(key);
        return result;
    }

    void SimpleResourceManager::loadBrush(const std::string& key, HBRUSH brush)
    {
        brushes.emplace(std::make_pair(key, brush));
    }

    HFONT SimpleResourceManager::getFont(const std::string& key)
    {
        HFONT result = fonts.at(key);
        return result;
    }

    void SimpleResourceManager::loadFont(const std::string& key, HFONT font)
    {
        fonts.emplace(std::make_pair(key, font));
    }
    COLORREF SimpleResourceManager::getColor(const std::string& key)
    {
        COLORREF result = colors.at(key);
        return result;
    }

    void SimpleResourceManager::loadColor(const std::string& key, COLORREF color)
    {
        colors.emplace(std::make_pair(key, color));
    }
}
