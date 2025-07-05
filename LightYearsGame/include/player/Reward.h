#pragma once
#include "framework/Actor.h"
#include <functional>

namespace ly
{
    class PlayerSpaceship;
    class Reward;

    using RewardFunc = std::function<void(PlayerSpaceship*)>;
    using RewardFactoryFunc = std::function<weak<Reward>(World*)>;

    class Reward :public Actor
    {
    public:
        Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed = 200.f);
        virtual void BeginPlay() override;
        virtual void Tick(float deltaTime) override;

    private:
        float mSpeed;
        RewardFunc mRewardFunc;

        virtual void OnActorBeginOverlap(Actor* other) override;
    };

    weak<Reward> CreateHealthReward(World* world);
    weak<Reward> CreateThreeWayShooterReward(World* world);
    weak<Reward> CreateFrontalWiperReward(World* world);
    weak<Reward> CreateLifeReward(World* world);

    weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc);

    void RewardHealth(PlayerSpaceship* player);
    void RewardThreeWayShooter(PlayerSpaceship* player);
    void RewardFrontalWiper(PlayerSpaceship* player);
    void RewardLife(PlayerSpaceship* player);
}