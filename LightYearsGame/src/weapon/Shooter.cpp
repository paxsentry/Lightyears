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

    Shooter::Shooter(Actor* owner)
        : mOwner{ owner },
        mCurrentLevel{ 1 },
        mMaxLevel{ 4 }
    {}
}