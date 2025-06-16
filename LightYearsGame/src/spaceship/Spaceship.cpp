#include "spaceship/Spaceship.h"

namespace ly
{
    Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
        :Actor{ owningWorld, texturePath },
        mVelocity{},
        mHealthComp{ 100.f, 100.f }
    {}

    void Spaceship::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        AddActorLocationOffset(GetVelocity() * deltaTime);
    }

    void Spaceship::SetVelocity(const sf::Vector2f& newVelocity)
    {
        mVelocity = newVelocity;
    }

    void Spaceship::Shoot()
    {}

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
        mHealthComp.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
        mHealthComp.onHealthChanged.BroadCast(10, 100, 120);
    }

    void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
    {
        LOG("Health is changed by %f, now it is %f/%f", amount, health, maxHealth);
    }
}