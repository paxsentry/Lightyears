#include "enemy/Boss.h"

namespace ly
{
    Boss::Boss(World* world)
        : EnemySpaceship{ world, "SpaceShooterRedux/PNG/playerShip3_red.png" }
        , mSpeed{ 100.f },
        mSwitchDistanceToEdge{ 100.f }
    {
        SetActorScale({ 2.f,2.f });
        SetActorRotation(-180.f);
    }

    void Boss::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
    }
}