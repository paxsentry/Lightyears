#pragma once
#include "weapon/Shooter.h"
#include "SFML/System.hpp"

namespace ly
{
    class BulletShooter : public Shooter
    {
    public:
        BulletShooter(Actor* owner, float cooldownTime = 0.3f);
        virtual bool IsOnCooldown() const override;

    private:
        virtual void ShootImplementation() override;
        sf::Clock mCooldownClock;
        float mCooldownTime;
    };
}