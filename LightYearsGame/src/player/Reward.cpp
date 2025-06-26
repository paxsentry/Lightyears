#include "player/Reward.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    Reward::Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed)
        :Actor{ world, texturePath },
        mRewardFunc{ rewardFunc },
        mSpeed{ speed }
    {}

    void Reward::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }

    void Reward::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        AddActorLocationOffset({ 0.f, mSpeed * deltaTime });
    }

    void Reward::OnActorBeginOverlap(Actor* other)
    {
        PlayerSpaceship* player = static_cast<PlayerSpaceship*>(other);

        if (player != nullptr && !player->IsPendingDestruction())
        {
            mRewardFunc(player);
        }
    }
}