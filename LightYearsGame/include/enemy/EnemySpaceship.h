#pragma once
#include "spaceship/Spaceship.h"
#include "player/Reward.h"

namespace ly
{
    class EnemySpaceship : public Spaceship
    {
    public:
        EnemySpaceship(World* owningWorld,
            const std::string& texturePath,
            float collisionDamage = 200.f,
            const List<RewardFactoryFunc> rewards = {
                CreateHealthReward,
                CreateThreeWayShooterReward,
                CreateFrontalWiperReward
            });

        virtual void Tick(float deltaTime) override;
        void SetScoreReward(unsigned int score);

    private:
        void SpawnReward();
        float mCollisionDamage;
        unsigned int mScoreReward;
        virtual void OnActorBeginOverlap(Actor* other) override;
        virtual void Blew() override;
        List<RewardFactoryFunc> mRewardFactory;
    };
}