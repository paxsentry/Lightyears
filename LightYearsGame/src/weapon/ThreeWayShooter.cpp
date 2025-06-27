#include "weapon/ThreeWayShooter.h"

namespace ly
{
    ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset)
        :Shooter{ owner },
        mShooterLeft{ owner, cooldownTime, localOffset + sf::Vector2f{10.f, -10.f}, -30.f },
        mShooterMid{ owner, cooldownTime, localOffset, 0.f },
        mShooterRight{ owner, cooldownTime, localOffset + sf::Vector2f{10.f, 10.f}, 30.f },
        mTopLevelShooterLeft{ owner, cooldownTime, localOffset + sf::Vector2f{10.f, 10.f}, 15.f },
        mTopLevelShooterRight{ owner, cooldownTime, localOffset + sf::Vector2f{10.f, -10.f}, -15.f }
    {
        mShooterLeft.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed01.png");
        mShooterMid.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed02.png");
        mShooterRight.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed01.png");
        mTopLevelShooterLeft.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed03.png");
        mTopLevelShooterRight.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed03.png");
    }

    void ThreeWayShooter::IncrementLevel(int amount)
    {
        Shooter::IncrementLevel(amount);
        mShooterLeft.IncrementLevel(amount);
        mShooterMid.IncrementLevel(amount);
        mShooterRight.IncrementLevel(amount);
        mTopLevelShooterLeft.IncrementLevel(amount);
        mTopLevelShooterRight.IncrementLevel(amount);
    }

    void ThreeWayShooter::ShootImplementation()
    {
        mShooterLeft.Shoot();
        mShooterMid.Shoot();
        mShooterRight.Shoot();

        if (GetCurrentLevel() == GetMaxLevel())
        {
            mTopLevelShooterLeft.Shoot();
            mTopLevelShooterRight.Shoot();
        }
    }
}