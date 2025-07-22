#include "framework/AssetsManager.h"
#include "framework/BackgroundLayer.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
    BackgroundLayer::BackgroundLayer(World* owningWorld, const List<std::string>& assetPaths, const sf::Vector2f& minVelocity, const sf::Vector2f& maxVelocity, float sizeMin, float sizeMax, int spriteCount, const sf::Color& tintColor)
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

        RefreshSprites();
    }

    void BackgroundLayer::RefreshSprites()
    {
        mSprites.clear();
        mVelocities.clear();

        for (int i = 0; i < mSpriteCount; ++i)
        {
            sf::Sprite newSprite{ Actor::GetEmptyTexture() };
            RandomSpriteTexture(newSprite);
            RandomSpriteTransform(newSprite, true);
            mSprites.push_back(newSprite);

            float velX = RandomRange(mMinVelocity.x, mMaxVelocity.x);
            float velY = RandomRange(mMinVelocity.y, mMaxVelocity.y);

            mVelocities.push_back(sf::Vector2f{ velX, velY });
        }

        SetColorTint(mTintColor);
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

    void BackgroundLayer::RandomSpriteTransform(sf::Sprite& sprite, bool randomY)
    {
        RandomSpritePosition(sprite, randomY);
        RandomSpriteRotation(sprite);
        RandomSpriteSize(sprite);
    }

    void BackgroundLayer::RandomSpritePosition(sf::Sprite& sprite, bool randomY)
    {
        auto windowSize = GetWorld()->GetWindowSize();
        auto bound = sprite.getGlobalBounds();

        float posX = RandomRange(0, windowSize.x);
        float posY = randomY ? RandomRange(0, windowSize.y) : -bound.size.y;

        sprite.setPosition(sf::Vector2f{ posX, posY });
    }

    void BackgroundLayer::RandomSpriteRotation(sf::Sprite& sprite)
    {
        sprite.setRotation(sf::degrees(RandomRange(0, 360.f)));
    }

    void BackgroundLayer::RandomSpriteSize(sf::Sprite& sprite) const
    {
        float size = RandomRange(mSizeMin, mSizeMax);
        sprite.setScale(sf::Vector2f{ size, size });
    }

    void BackgroundLayer::RandomSpriteVelocity(sf::Sprite& sprite)
    {
        float velX = RandomRange(mMinVelocity.x, mMaxVelocity.x);
        float velY = RandomRange(mMinVelocity.y, mMaxVelocity.y);
        //mVelocities[i] = sf::Vector2f{ velX, velY };
    }

    void BackgroundLayer::SetColorTint(const sf::Color& tintColor)
    {
        mTintColor = tintColor;
        for (sf::Sprite& sprite : mSprites)
        {
            sprite.setColor(mTintColor);
        }
    }

    void BackgroundLayer::SetSpriteCount(int newCount)
    {
        mSpriteCount = newCount;
        RefreshSprites();
    }

    void BackgroundLayer::SetVelocities(const sf::Vector2f& minVel, const sf::Vector2f& maxVel)
    {
        mMinVelocity = minVel;
        mMaxVelocity = maxVel;

        for (int i = 0; i < mVelocities.size(); ++i)
        {
            float velX = RandomRange(mMinVelocity.x, mMaxVelocity.x);
            float velY = RandomRange(mMinVelocity.y, mMaxVelocity.y);
            mVelocities[i] = sf::Vector2f{ velX, velY };
        }
    }

    void BackgroundLayer::SetSizes(float minSize, float maxSize)
    {
        mSizeMin = minSize;
        mSizeMax = maxSize;

        for (int i = 0; i < mSprites.size(); ++i)
        {
            RandomSpriteSize(mSprites[i]);
        }
    }

    void BackgroundLayer::Render(sf::RenderWindow& window)
    {
        Actor::Render(window);
        for (const sf::Sprite& sprite : mSprites)
        {
            window.draw(sprite);
        }
    }

    void BackgroundLayer::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        for (int i = 0; i < mSprites.size(); ++i)
        {
            sf::Sprite& sprite = mSprites[i];
            sf::Vector2f& velocity = mVelocities[i];

            sprite.setPosition(sprite.getPosition() + velocity * deltaTime);
            if (IsSpriteOffScreen(sprite))
            {
                RandomSpriteTexture(sprite);
                RandomSpriteTransform(sprite);
                float velX = RandomRange(mMinVelocity.x, mMaxVelocity.x);
                float velY = RandomRange(mMinVelocity.y, mMaxVelocity.y);
                mVelocities[i] = sf::Vector2f{ velX, velY };
            }
        }
    }

    shared<sf::Texture> BackgroundLayer::GetRandomTexture() const
    {
        int randomIndex = (int)(RandomRange(0, mTextures.size()));

        return mTextures[randomIndex];
    }

    bool BackgroundLayer::IsSpriteOffScreen(sf::Sprite& sprite) const
    {
        auto bound = sprite.getGlobalBounds();
        auto windowSize = GetWorld()->GetWindowSize();
        auto spritePos = sprite.getPosition();

        if (spritePos.x < -bound.size.x || spritePos.x > windowSize.x + bound.size.x)
        {
            return true;
        }

        if (spritePos.y < -bound.size.y || spritePos.y > windowSize.y + bound.size.y)
        {
            return true;
        }

        return false;
    }
}