#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetsManager.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath)
        :mOwningWorld{ owningWorld },
        mHasBeganPlay{ false },
        mSprite{ sf::Sprite::Sprite(GetEmptyTexture()) },
        mTexture{ }
    {
        SetTexture(texturePath);
    }

    Actor::~Actor()
    {
        LOG("Actor destroyed");
    }

    void Actor::BeginPlayInternal()
    {
        if (!mHasBeganPlay)
        {
            mHasBeganPlay = true;
            BeginPlay();
        }
    }

    void Actor::TickInternal(float deltaTime)
    {
        if (!IsPendingDestruction())
        {
            Tick(deltaTime);
        }
    }

    void Actor::BeginPlay()
    {
        LOG("Actor begin play");
    }

    void Actor::Tick(float deltaTime)
    {
        LOG("Actor ticking at FPS: %f", 1.f / deltaTime);
    }

    void Actor::SetTexture(const std::string& texturePath)
    {
        mTexture = AssetsManager::Get().LoadTexture(texturePath);

        if (!mTexture)
        {
            LOG("Invalid texture path: %s", texturePath);
            return;
        }

        mSprite.setTexture(*mTexture);

        int textureWidth = mTexture->getSize().x;
        int textureHeight = mTexture->getSize().y;

        mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
    }

    void Actor::Render(sf::RenderWindow& window)
    {
        if (IsPendingDestruction()) return;

        window.draw(mSprite);
    }

    // This function is to create an empty texture, since SFML 3.0 there is NO cosntructor without texture
    const sf::Texture& Actor::GetEmptyTexture()
    {
        sf::RenderTexture renderTexture;
        sf::RectangleShape rect(sf::Vector2f(0.f, 0.f));

        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(rect);
        renderTexture.display(); 

        static sf::Texture texture = renderTexture.getTexture();

        return texture;
    }
}