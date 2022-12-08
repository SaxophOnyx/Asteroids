#pragma once

#include "ISimpleResourceManager.h"
#include <unordered_map>

namespace ast
{
    class SimpleResourceManager: public ISimpleResourceManager
    {
        public:
        SimpleResourceManager(std::string folderPath);
        SimpleResourceManager(SimpleResourceManager&) = delete;
        virtual ~SimpleResourceManager();

        // Унаследовано через ISimpleResourceManager
        virtual HBITMAP& getImage(const std::string& key) override;
        virtual void loadImage(const std::string& key, const std::string& path) override;
        virtual HPEN getPen(const std::string& key) override;
        virtual void loadPen(const std::string& key, HPEN pen) override;
        virtual HBRUSH getBrush(const std::string& key) override;
        virtual void loadBrush(const std::string& key, HBRUSH brush) override;
        virtual HFONT getFont(const std::string& key) override;
        virtual void loadFont(const std::string& key, HFONT font) override;
        virtual COLORREF getColor(const std::string& key) override;
        virtual void loadColor(const std::string& key, COLORREF color) override;

        private:
        std::string folderPath;
        std::unordered_map<std::string, HBITMAP> images;
        std::unordered_map<std::string, HPEN> pens;
        std::unordered_map<std::string, HBRUSH> brushes;
        std::unordered_map<std::string, HFONT> fonts;
        std::unordered_map<std::string, COLORREF> colors;
    };
}
