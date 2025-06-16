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
        mHealthComp.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
        mHealthComp.onHealthEmtpy.BindAction(GetWeakRef(), &Spaceship::Blow);
    }

    void Spaceship::ApplyDamage(float amount)
    {
        mHealthComp.ChangeHealth(-amount);
    }

    void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
    {
        LOG("Health is changed by %f, now it is %f/%f", amount, health, maxHealth);
    }

    void Spaceship::OnTakenDamage(float amount, float health, float maxHealth)
    {
    
    }

    void Spaceship::Blow()
    {
        Destroy();
    }
}