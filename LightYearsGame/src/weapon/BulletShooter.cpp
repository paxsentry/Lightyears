#include "framework/Core.h"
#include "framework/World.h"
#include "weapon/Bullet.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    BulletShooter::BulletShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localPositionOffset, float localRotationOffset)
        : Shooter{ owner },
        mCooldownClock{},
        mCooldownTime{ cooldownTime },
        mLocalPositionOffset{ localPositionOffset },
        mLocalRotationOffset{ localRotationOffset }
    {}

    bool BulletShooter::IsOnCooldown() const
    {
        if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime)
        {
            return false;
        }

        return true;
    }

    void BulletShooter::ShootImplementation()
    {
        sf::Vector2f ownerForwardDirection = GetOwner()->GetActorForwardDirection();
        sf::Vector2f ownerRightDirection = GetOwner()->GetActorRightDirection();

        mCooldownClock.restart();
        weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(),
            "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"
        );
        newBullet.lock()->SetSpeed(mBulletSpeed);
        newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() +
            ownerForwardDirection * mLocalPositionOffset.x +
            ownerRightDirection * mLocalPositionOffset.y);
        newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation().asDegrees() +
            mLocalRotationOffset);
    }
}