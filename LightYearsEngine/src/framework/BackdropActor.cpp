#include "framework/BackdropActor.h"
#include "framework/World.h"

namespace ly
{
    BackdropActor::BackdropActor(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
        :Actor{ owningWorld, texturePath },
        mMovingVelocity{ velocity }
        , mLeftShift{ 0.f },
        mTopShift{ 0.f }
    {
        auto windowSize = owningWorld->GetWindowSize();
        GetSprite().setOrigin(sf::Vector2f{ 0.f,0.f });
        GetSprite().setTextureRect(sf::IntRect{ sf::Vector2i{0,0}, sf::Vector2i{(int)windowSize.x, (int)windowSize.y} });
        SetTextureRepeated(true);
    }

    void BackdropActor::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        mLeftShift += deltaTime * mMovingVelocity.x;
        mTopShift += deltaTime * mMovingVelocity.y;

        sf::IntRect currentRect = GetSprite().getTextureRect();
        currentRect.position.x = mLeftShift;
        currentRect.position.y = mTopShift;

        GetSprite().setTextureRect(currentRect);
    }
}