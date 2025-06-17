#include "framework/MathUtility.h"
#include "VFX/Particle.h"

namespace ly
{
    Particle::Particle(World* owningWorld, const std::string& texturePath)
        :Actor{ owningWorld, texturePath },
        mVelocity{},
        mLifetime{ 1.f },
        mTimer{}
    {}

    void Particle::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        Move(deltaTime);
        Fade(deltaTime);

        if (mTimer.getElapsedTime().asSeconds() >= mLifetime)
        {
            Destroy();
        }
    }

    void Particle::RandomVelocity(float minSpeed, float maxSpeed)
    {
        mVelocity = RandomUnitVector() * RandomRange(minSpeed, maxSpeed);
    }

    void Particle::RandomSize(float minSize, float maxSize)
    {
        float randScale = RandomRange(minSize, maxSize);

        GetSprite().setScale(sf::Vector2{ randScale, randScale });
    }

    void Particle::RandomLifetime(float minLifetime, float maxLifetime)
    {
        mLifetime = RandomRange(minLifetime, maxLifetime);
    }

    void Particle::Move(float deltaTime)
    {
        AddActorLocationOffset(mVelocity * deltaTime);
    }

    void Particle::Fade(float deltaTime)
    {
        float elapsedTime = mTimer.getElapsedTime().asSeconds();
        GetSprite().setColor(LerpColor(GetSprite().getColor(), sf::Color(255, 255, 255, 0), elapsedTime / mLifetime));
        GetSprite().setScale(LerpVector2f(GetSprite().getScale(), sf::Vector2f{ 0,0 }, elapsedTime / mLifetime));
    }
}