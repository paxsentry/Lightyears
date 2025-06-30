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

        template<typename T>
        void CleanUniqueRef(Dictionary<std::string, shared<T>>& container);
    };

    template<typename T>
    inline void AssetsManager::CleanUniqueRef(Dictionary<std::string, shared<T>>& container)
    {
        for (auto iter = container.begin(); iter != container.end();)
        {
            if (iter->second.unique())
            {
                LOG("Cleaning: %s", iter->first.c_str());
                iter = container.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
}