#include "enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
        : EnemySpaceship{ owningWorld, texturePath },
        mShooter{ new BulletShooter{this} }
    {
        SetVelocity(velocity);
        // These two are needed to have the correct facing and shooting of the Vanguard
        SetActorRotation(180.f);
        SetActorScale(sf::Vector2f{ 1.f,-1.f });
        mShooter->SetBulletSpeed(700.f);
    }

    void Vanguard::Shoot()
    {
        mShooter->Shoot();
    }

    void Vanguard::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
    }
}