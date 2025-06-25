#pragma once
#include "weapon/BulletShooter.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class ThreeWayShooter : public Shooter
    {
    public:
        ThreeWayShooter(Actor* owner, float cooldownTime = 0.3f, const sf::Vector2f& localOffset = { 0.f, 0.f });

    private:
        BulletShooter mShooterLeft;
        BulletShooter mShooterMid;
        BulletShooter mShooterRight;

        virtual void ShootImplementation() override;
    };
}