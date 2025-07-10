#include "enemy/Boss.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
    Boss::Boss(World* world)
        : EnemySpaceship{ world, "SpaceShooterRedux/PNG/playerShip3_red.png" }
        , mSpeed{ 100.f },
        mSwitchDistanceToEdge{ 100.f },
        mBaseShooterLeft{ this, 1.f, {50.f, -50.f} },
        mBaseShooterRight{ this, 1.f, {50.f, 50.f} }
    {
        SetActorScale({ 2.5f,2.f });
        SetActorRotation(-180.f);
        SetVelocity({ mSpeed, 0.f });
        SetRewardWeight(0);
        HealthComponent& healthComp = GetHealthComponent();
        healthComp.SetInitalHealth(3000.f, 3000.f);
        SetScoreReward(1000);
    }

    void Boss::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        ShootBaseShooters();
        CheckMove();
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
}