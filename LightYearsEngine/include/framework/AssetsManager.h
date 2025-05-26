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

    protected:
        AssetsManager();
    private:
        static unique<AssetsManager> assetsManager;
        Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
    };
}