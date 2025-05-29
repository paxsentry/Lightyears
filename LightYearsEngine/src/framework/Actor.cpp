#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetsManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

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
    }

    void Actor::Tick(float deltaTime)
    {
    }

    void Actor::SetTexture(const std::string& texturePath)
    {
        mTexture = AssetsManager::Get().LoadTexture(texturePath);

        if (!mTexture)
        {
            LOG("Invalid texture path: %s", texturePath.c_str());
            return;
        }

        mSprite.setTexture(*mTexture);

        int textureWidth = mTexture->getSize().x;
        int textureHeight = mTexture->getSize().y;

        mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
        CenterPivot();
    }

    void Actor::Render(sf::RenderWindow& window)
    {
        if (IsPendingDestruction()) return;

        window.draw(mSprite);
    }

    void Actor::SetActorLocation(const sf::Vector2f& newLoc)
    {
        mSprite.setPosition(newLoc);
    }

    void Actor::SetActorRotation(const float newRot)
    {
        sf::Angle newAngle = sf::degrees(newRot);
        SetActorRotation(newAngle);
    }

    void Actor::SetActorRotation(const sf::Angle& newRot)
    {
        mSprite.setRotation(newRot);
    }

    void Actor::AddActorLocationOffset(const sf::Vector2f& offset)
    {
        SetActorLocation(GetActorLocation() + offset);
    }

    void Actor::AddActorRotationOffset(const sf::Angle& offset)
    {
        SetActorRotation(GetActorRotation() + offset);
    }

    sf::Vector2f Actor::GetActorLocation() const
    {
        return mSprite.getPosition();
    }

    sf::Angle Actor::GetActorRotation() const
    {
        return mSprite.getRotation();
    }

    sf::Vector2f Actor::GetActorForwardDirection() const
    {
        return RotationToVector(GetActorRotation().asDegrees());
    }

    sf::Vector2f Actor::GetActorRightDirection() const
    {
        return RotationToVector(GetActorRotation().asDegrees() + 90.f);
    }

    sf::Vector2u Actor::GetWindowSize() const
    {
        return mOwningWorld->GetWindowSize();
    }

    void Actor::CenterPivot()
    {
        sf::FloatRect bound = mSprite.getGlobalBounds();
        mSprite.setOrigin(sf::Vector2f(bound.size.x / 2.f, bound.size.y / 2.f));
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