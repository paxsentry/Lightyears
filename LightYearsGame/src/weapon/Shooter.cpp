#include "weapon/Shooter.h"

namespace ly
{
    void Shooter::Shoot()
    {
        if (CanShoot() && !IsOnCooldown())
        {
            ShootImplementation();
        }
    }

    void Shooter::IncrementLevel(int amount)
    {
        if (mCurrentLevel < mMaxLevel)
        {
            mCurrentLevel += amount;
        }
    }

    void Shooter::SetCurrentLevel(int level)
    {
        mCurrentLevel = level;
    }

    Shooter::Shooter(Actor* owner)
        : mOwner{ owner },
        mCurrentLevel{ 1 },
        mMaxLevel{ 4 }
    {}
}