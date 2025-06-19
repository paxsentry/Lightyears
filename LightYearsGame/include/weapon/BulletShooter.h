#pragma once
#include "SFML/System.hpp"
#include "weapon/Shooter.h"

namespace ly
{
    class BulletShooter : public Shooter
    {
    public:
        BulletShooter(Actor* owner, float cooldownTime = 0.3f);
        virtual bool IsOnCooldown() const override;
        void SetBulletSpeed(float bulletSpeed) { mBulletSpeed = bulletSpeed; }
        void SetBulletDamage(float bulletDamage) { mBulletDamage = bulletDamage; }

    private:
        virtual void ShootImplementation() override;
        sf::Clock mCooldownClock;
        float mCooldownTime;
        float mBulletSpeed = 900.f;
        float mBulletDamage = 20.f;
    };
}