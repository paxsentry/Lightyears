#include "weapon/Bullet.h"

namespace ly
{
    Bullet::Bullet(World* owningWorld, Actor* owner, const std::string& texturePath, float speed, float damage)
        : Actor{ owningWorld, texturePath },
        mOwner{ owner },
        mSpeed{ speed },
        mDamage{ damage }
    {
    }

    void Bullet::SetSpeed(float newSpeed)
    {
        mSpeed = newSpeed;
    }

    void Bullet::SetDamage(float newDamage)
    {
        mDamage = newDamage;
    }

    void Bullet::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);

        if (IsActorOutOfWindowBounds())
        {
            Destroy();
        }
    }

    void Bullet::Move(float deltaTime)
    {
        AddActorLocationOffset(GetActorForwardDirection() * mSpeed * deltaTime);
    }
}