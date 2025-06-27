#include "weapon/FrontalWiper.h"

namespace ly
{
    FrontalWiper::FrontalWiper(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset, float width)
        : Shooter{ owner },
        mShooter1{ owner, cooldownTime, {localOffset.x, localOffset.y - width / 2.f}, 0.f },
        mShooter2{ owner, cooldownTime, {localOffset.x, localOffset.y - width / 6.f}, 0.f },
        mShooter3{ owner, cooldownTime, {localOffset.x, localOffset.y + width / 6.f}, 0.f },
        mShooter4{ owner, cooldownTime, {localOffset.x, localOffset.y + width / 2.f}, 0.f },
        mWidth{ width },
        mShooter5{ owner, .1f, {localOffset.x, localOffset.y + width / 1.5f}, 15.f },
        mShooter6{ owner, .1f, {localOffset.x, localOffset.y - width / 1.5f}, -15.f }
    {
        mShooter1.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserGreen10.png");
        mShooter2.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserBlue16.png");
        mShooter3.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserBlue16.png");
        mShooter4.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserGreen10.png");
        mShooter5.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserGreen11.png");
        mShooter6.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserGreen11.png");
    }

    void FrontalWiper::IncrementLevel(int amount)
    {
        Shooter::IncrementLevel(amount);
        mShooter1.IncrementLevel(amount);
        mShooter2.IncrementLevel(amount);
        mShooter3.IncrementLevel(amount);
        mShooter4.IncrementLevel(amount);
        mShooter5.IncrementLevel(amount);
        mShooter6.IncrementLevel(amount);
    }

    void FrontalWiper::ShootImplementation()
    {
        mShooter1.Shoot();
        mShooter2.Shoot();
        mShooter3.Shoot();
        mShooter4.Shoot();

        if (GetCurrentLevel() == GetMaxLevel())
        {
            mShooter5.Shoot();
            mShooter6.Shoot();
        }
    }
}