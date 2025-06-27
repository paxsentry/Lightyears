#include "enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"

namespace ly
{
    EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage, const List<RewardFactoryFunc> rewards)
        :Spaceship{ owningWorld, texturePath },
        mCollisionDamage{ collisionDamage },
        mRewardFactory{ rewards }
    {
        SetTeamId(2);
    }

    void EnemySpaceship::OnActorBeginOverlap(Actor* other)
    {
        Spaceship::OnActorBeginOverlap(other);

        if (IsOtherHostile(other))
        {
            other->ApplyDamage(mCollisionDamage);
        }
    }

    void EnemySpaceship::Blew()
    {
        SpawnReward();
    }

    void EnemySpaceship::SpawnReward()
    {
        if (mRewardFactory.size() == 0) return;

        int pick = (int)RandomRange(0, mRewardFactory.size());

        if (pick >= 0 && pick < mRewardFactory.size())
        {
            weak<Reward> newReward = mRewardFactory[pick](GetWorld());
            newReward.lock()->SetActorLocation(GetActorLocation());
        }
    }

    void EnemySpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);

        if (IsActorOutOfWindowBounds(GetActorGlobalBounds().size.x * 2.f))
        {
            Destroy();
        }
    }
}