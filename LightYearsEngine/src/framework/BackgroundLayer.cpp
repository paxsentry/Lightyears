#include "framework/AssetsManager.h"
#include "framework/BackgroundLayer.h"
#include "framework/MathUtility.h"

namespace ly
{
    BackgroundLayer::BackgroundLayer(World* owningWorld, const List<std::string>& assetPaths, const sf::Vector2f& minVelocity, const sf::Vector2f& maxVelocity, float sizeMin, float sizeMax, int spriteCount, const sf::Color tintColor)
        : Actor{ owningWorld },
        mMinVelocity{ minVelocity },
        mMaxVelocity{ maxVelocity },
        mSizeMin{ sizeMin },
        mSizeMax{ sizeMax },
        mSpriteCount{ spriteCount },
        mTintColor{ tintColor }
    {
        SetAssets(assetPaths);
    }

    void BackgroundLayer::SetAssets(const List<std::string>& assetPaths)
    {
        for (const std::string& texturePath : assetPaths)
        {
            shared<sf::Texture> newTexture = AssetsManager::Get().LoadTexture(texturePath);
            mTextures.push_back(newTexture);
        }
    }

    void BackgroundLayer::RefreshSprites()
    {
        mSprites.clear();
        mVelocities.clear();

        for (int i = 0; i < mSpriteCount; ++i)
        {
            sf::Sprite newSprite{ Actor::GetEmptyTexture() };
            RandomSpriteTexture(newSprite);
        }
    }

    void BackgroundLayer::RandomSpriteTexture(sf::Sprite& sprite)
    {
        if (mTextures.size() > 0)
        {
            shared<sf::Texture> pickedTexture = GetRandomTexture();
            sprite.setTexture(*(pickedTexture.get()));
            sprite.setTextureRect(sf::IntRect{ {0,0},{(int)pickedTexture->getSize().x, (int)pickedTexture->getSize().y} });
            sf::FloatRect bound = sprite.getGlobalBounds();
            sprite.setOrigin({ bound.size.x / 2.f, bound.size.y / 2.f });
        }
    }

    shared<sf::Texture> BackgroundLayer::GetRandomTexture() const
    {
        int randomIndex = (int)(RandomRange(0, mTextures.size()));

        return mTextures[randomIndex];
    }
}