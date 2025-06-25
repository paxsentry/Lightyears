#include "weapon/FrontalWiper.h"

namespace ly
{
    FrontalWiper::FrontalWiper(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset, float width)
        : Shooter{ owner },
        mShooter1{ owner, cooldownTime, {localOffset.x, localOffset.y - width / 2.f}, 0.f },
        mShooter2{ owner, cooldownTime, {localOffset.x, localOffset.y - width / 6.f}, 0.f },
        mShooter3{ owner, cooldownTime, {localOffset.x, localOffset.y + width / 6.f}, 0.f },
        mShooter4{ owner, cooldownTime, {localOffset.x, localOffset.y + width / 2.f}, 0.f },
        mWidth {width}
    {
        mShooter1.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserGreen10.png");
        mShooter2.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserBlue16.png");
        mShooter3.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserBlue16.png");
        mShooter4.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserGreen10.png");
    }

    void FrontalWiper::ShootImplementation()
    {
        mShooter1.Shoot();
        mShooter2.Shoot();
        mShooter3.Shoot();
        mShooter4.Shoot();
    }
}