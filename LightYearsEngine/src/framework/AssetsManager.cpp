#include "framework/AssetsManager.h"

namespace ly
{
    unique<AssetsManager> AssetsManager::assetsManager{ nullptr };

    AssetsManager::AssetsManager():
        mRootDirectory{}
    {
    }

    AssetsManager& AssetsManager::Get()
    {
        if (!assetsManager)
        {
            assetsManager = unique<AssetsManager>{new AssetsManager};
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

    void AssetsManager::CleanCycle()
    {
        for (auto iter = mLoadedTextureMap.begin(); iter != mLoadedTextureMap.end();)
        {
            if (iter->second.unique())
            {
                LOG("Cleaning texture: %s", iter->first.c_str());
                iter = mLoadedTextureMap.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    void AssetsManager::SetAssetsRootDirectory(const std::string& directory)
    {
        mRootDirectory = directory;
    }
}