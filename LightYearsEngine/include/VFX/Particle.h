#pragma once
#include "framework/Actor.h"

namespace ly
{
    class Particle : public Actor
    {
    public:
        Particle(World* owningWorld, const std::string& texturePath);
        virtual void Tick(float deltaTime) override;

        void RandomVelocity(float minSpeed, float maxSpeed);
        void RandomSize(float minSize, float maxSize);
        void RandomLifetime(float minLifetime, float maxLifetime);

    private:
        sf::Vector2f mVelocity;
        float mLifetime;
        sf::Clock mTimer;

        void Move(float deltaTime);
        void Fade(float deltaTime);
    };
}