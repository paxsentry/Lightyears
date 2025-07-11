#pragma once
#include "SFML/System.hpp"
#include "weapon/Shooter.h"

namespace ly
{
    class BulletShooter : public Shooter
    {
    public:
        BulletShooter(Actor* owner,
            float cooldownTime = 1.f,
            const sf::Vector2f& localPositionOffset = { 0.f,0.f },
            float localRotationOffset = 0.f,
            const std::string& bulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        virtual bool IsOnCooldown() const override;
        void SetBulletSpeed(float bulletSpeed) { mBulletSpeed = bulletSpeed; }
        void SetBulletDamage(float bulletDamage) { mBulletDamage = bulletDamage; }
        void SetBulletTexturePath(const std::string& path);
        virtual void IncrementLevel(int amount) override;
        virtual void SetCurrentLevel(int level) override;

    private:
        virtual void ShootImplementation() override;
        sf::Clock mCooldownClock;
        float mCooldownTime;
        float mBulletSpeed = 900.f;
        float mBulletDamage = 20.f;

        sf::Vector2f mLocalPositionOffset;
        float mLocalRotationOffset;
        std::string mBulletTexturePath;
    };
}