#include "player/PlayerSpaceship.h"
#include "player/Reward.h"
#include "weapon/FrontalWiper.h"
#include "weapon/ThreeWayShooter.h"
#include "framework/World.h"

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
        PlayerSpaceship* player = dynamic_cast<PlayerSpaceship*>(other);

        if (player != nullptr && !player->IsPendingDestruction())
        {
            mRewardFunc(player);
            Destroy();
        }
    }

    weak<Reward> CreateHealthReward(World* world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/pill_green.png", RewardHealth);
    }

    weak<Reward> CreateThreeWayShooterReward(World* world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/powerupRed_star.png", RewardThreeWayShooter);
    }

    weak<Reward> CreateFrontalWiperReward(World* world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/powerupGreen_star.png", RewardFrontalWiper);
    }

    weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc)
    {
        weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc);

        return reward;
    }

    void RewardHealth(PlayerSpaceship* player)
    {
        static float reward = 10.f;
        if (player && !player->IsPendingDestruction())
        {
            player->GetHealthComponent().ChangeHealth(reward);
        }
    }

    void RewardThreeWayShooter(PlayerSpaceship* player)
    {
        if (player && !player->IsPendingDestruction())
        {
            player->SetShooter(unique<Shooter>{new ThreeWayShooter{ player, 0.4f, {50.f, 0.f} }});
        }
    }

    void RewardFrontalWiper(PlayerSpaceship* player)
    {
        if (player && !player->IsPendingDestruction())
        {
            player->SetShooter(unique<Shooter>{new FrontalWiper{ player, 0.2f, {50.f, 0.f} }});
        }
    }
}