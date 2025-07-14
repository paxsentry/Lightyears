#include "enemy/Boss.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
    Boss::Boss(World* world)
        : EnemySpaceship{ world, "SpaceShooterRedux/PNG/playerShip3_red.png" },
        mSpeed{ 100.f },
        mBaseSpeed{ 100.f },
        mSwitchDistanceToEdge{ 100.f },
        mBaseShooterLeft{ this, 1.5f, {50.f, -50.f} },
        mBaseShooterRight{ this, 1.f, {50.f, 50.f} },
        mThreewayShooter{ this, 5.f, {100.f, 0.f} },
        mFrontalWiperLeft{ this, 5.f, {80.f, -100.f} },
        mFrontalWiperRight{ this, 5.f, {80.f, 100.f} },
        mStage{ 1 },
        mFinalStageShooterLeft{ this, 0.3f, {50.f, -150.f} },
        mFinalStageShooterRight{ this, 0.3f, {50.f, -150.f} }
    {
        SetActorScale({ 2.5f,2.f });
        SetActorRotation(-180.f);
        SetVelocity({ mSpeed, 0.f });
        SetRewardWeight(0);
        SetScoreReward(1000);
    }

    void Boss::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        ShootBaseShooters();
        ShootThreeWayShooters();
        ShootFrontalWiperShooters();
        if (mStage == 4)
        {
            mFinalStageShooterLeft.Shoot();
            mFinalStageShooterRight.Shoot();
        }

        CheckMove();
    }

    void Boss::BeginPlay()
    {
        EnemySpaceship::BeginPlay();
        HealthComponent& healthComp = GetHealthComponent();
        healthComp.SetInitalHealth(3000.f, 3000.f);
        healthComp.onHealthChanged.BindAction(GetWeakRef(), &Boss::HealthChanged);
    }

    void Boss::CheckMove()
    {
        if (GetActorLocation().x > GetWindowSize().x - mSwitchDistanceToEdge)
        {
            SetVelocity({ -mSpeed, 0.f });
        }
        else if (GetActorLocation().x < mSwitchDistanceToEdge)
        {
            SetVelocity({ mSpeed, 0.f });
        }
    }

    void Boss::ShootBaseShooters()
    {
        mBaseShooterLeft.Shoot();
        mBaseShooterRight.Shoot();
    }

    void Boss::ShootThreeWayShooters()
    {
        mThreewayShooter.Shoot();
    }

    void Boss::ShootFrontalWiperShooters()
    {
        mFrontalWiperLeft.Shoot();
        mFrontalWiperRight.Shoot();
    }

    void Boss::SetStage(int stage)
    {
        mStage = stage;
        mBaseShooterLeft.SetCurrentLevel(mStage);
        mBaseShooterRight.SetCurrentLevel(mStage);
        mThreewayShooter.SetCurrentLevel(mStage);
        mFrontalWiperLeft.SetCurrentLevel(mStage);
        mFrontalWiperRight.SetCurrentLevel(mStage);
        mSpeed = mStage * mBaseSpeed;
    }

    void Boss::HealthChanged(float amount, float currentHealth, float maxHealth)
    {
        float percentLeft = currentHealth / maxHealth;

        if (percentLeft < 0.7f && percentLeft > 0.5f)
        {
            SetStage(2);
        }

        if (percentLeft < 0.5f && percentLeft > 0.2f)
        {
            SetStage(3);
        }

        if (percentLeft < 0.3f)
        {
            SetStage(4);
        }
    }
}