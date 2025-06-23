#pragma once
#include "enemy/EnemySpaceship.h"

namespace ly
{
    class BulletShooter;

    class Vanguard : public EnemySpaceship
    {
    public:
        Vanguard(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png", const sf::Vector2f& velocity = { 0.f, 150.f });
        virtual void Tick(float deltaTime);

    private:
        unique<BulletShooter> mShooter;
        virtual void Shoot() override;
    };
}