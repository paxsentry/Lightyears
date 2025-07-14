#pragma once
#include "enemy/EnemySpaceship.h"
#include "weapon/BulletShooter.h"
#include "weapon/ThreewayShooter.h"
#include "weapon/FrontalWiper.h"

namespace ly
{
    class Boss : public EnemySpaceship
    {
    public:
        Boss(World* world);
        virtual void Tick(float deltaTime) override;
        virtual void BeginPlay() override;

    private:
        float mSpeed;
        float mBaseSpeed;
        float mSwitchDistanceToEdge;

        void CheckMove();

        BulletShooter mBaseShooterLeft;
        BulletShooter mBaseShooterRight;

        ThreeWayShooter mThreewayShooter;
        FrontalWiper mFrontalWiperLeft;
        FrontalWiper mFrontalWiperRight;

        BulletShooter mFinalStageShooterLeft;
        BulletShooter mFinalStageShooterRight;

        void ShootBaseShooters();
        void ShootThreeWayShooters();
        void ShootFrontalWiperShooters();

        int mStage;
        void SetStage(int stage);
        void HealthChanged(float amount, float currentHealth, float maxHealth);
    };
}