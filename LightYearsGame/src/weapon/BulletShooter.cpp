#include "framework/Core.h"
#include "framework/World.h"
#include "weapon/Bullet.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    BulletShooter::BulletShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localPositionOffset, float localRotationOffset, const std::string& bulletTexturePath)
        : Shooter{ owner },
        mCooldownClock{},
        mCooldownTime{ cooldownTime },
        mLocalPositionOffset{ localPositionOffset },
        mLocalRotationOffset{ localRotationOffset },
        mBulletTexturePath{ bulletTexturePath }
    {}

    bool BulletShooter::IsOnCooldown() const
    {
        if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime / GetCurrentLevel())
        {
            return false;
        }

        return true;
    }

    void BulletShooter::SetBulletTexturePath(const std::string& path)
    {
        mBulletTexturePath = path;
    }

    void BulletShooter::IncrementLevel(int amount)
    {
        Shooter::IncrementLevel(amount);
    }

    void BulletShooter::ShootImplementation()
    {
        sf::Vector2f ownerForwardDirection = GetOwner()->GetActorForwardDirection();
        sf::Vector2f ownerRightDirection = GetOwner()->GetActorRightDirection();

        mCooldownClock.restart();
        weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(),
            mBulletTexturePath
        );
        newBullet.lock()->SetSpeed(mBulletSpeed);
        newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() +
            ownerForwardDirection * mLocalPositionOffset.x +
            ownerRightDirection * mLocalPositionOffset.y);
        newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation().asDegrees() +
            mLocalRotationOffset);
    }
}