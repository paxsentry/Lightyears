#include "framework/AssetsManager.h"

namespace ly
{
    unique<AssetsManager> AssetsManager::assetsManager{ nullptr };

    AssetsManager::AssetsManager() :
        mRootDirectory{}
    {}

    AssetsManager& AssetsManager::Get()
    {
        if (!assetsManager)
        {
            assetsManager = unique<AssetsManager>{ new AssetsManager };
        }

        return *assetsManager;
    }

    shared<sf::Texture> AssetsManager::LoadTexture(const std::string& path)
    {
        auto found = mLoadedTextureMap.find(path);

        if (found != mLoadedTextureMap.end())
        {
            return found->second;
        }

        shared<sf::Texture> newTexture{ new sf::Texture };
        if (newTexture->loadFromFile(mRootDirectory + path))
        {
            mLoadedTextureMap.insert({ path, newTexture });
            return newTexture;
        }

        return shared<sf::Texture>{ nullptr };
    }

    shared<sf::Font> AssetsManager::LoadFont(const std::string& path)
    {
        auto found = mLoadedFontMap.find(path);

        if (found != mLoadedFontMap.end())
        {
            return found->second;
        }

        shared<sf::Font> newFont{ new sf::Font };
        if (newFont->openFromFile(mRootDirectory + path))
        {
            mLoadedFontMap.insert({ path, newFont });
            return newFont;
        }

        return shared<sf::Font>{nullptr};
    }

    void AssetsManager::CleanCycle()
    {
        CleanUniqueRef(mLoadedTextureMap);
        CleanUniqueRef(mLoadedFontMap);
    }

    void AssetsManager::SetAssetsRootDirectory(const std::string& directory)
    {
        mRootDirectory = directory;
    }
}