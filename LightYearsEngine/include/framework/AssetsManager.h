#pragma once
#include <SFML/Graphics.hpp>
#include "Core.h"

namespace ly
{
    class AssetsManager
    {
    public:
        static AssetsManager& Get();
        shared<sf::Texture> LoadTexture(const std::string& path);
        shared<sf::Font> LoadFont(const std::string& path);
        void CleanCycle();
        void SetAssetsRootDirectory(const std::string& directory);

    protected:
        AssetsManager();
    private:
        static unique<AssetsManager> assetsManager;
        Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
        Dictionary<std::string, shared<sf::Font>> mLoadedFontMap;
        std::string mRootDirectory;
    };
}