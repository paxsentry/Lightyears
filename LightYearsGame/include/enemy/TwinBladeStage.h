#pragma once
#include "gameplay/GameStage.h"
#include <SFML/Graphics.hpp>
#include "framework/TimerManager.h"

namespace ly
{
    class TwinBladeStage : public GameStage
    {
    public:
        TwinBladeStage(World* world);
        virtual void StartStage() override;

    private:
        void SpawnTwinBlade();
        virtual void StageFinished() override;

        float mSpawnInterval;
        float mSpawnDistanceToCenter;

        sf::Vector2f mLeftSpawnLocation;
        sf::Vector2f mRightSpawnLocation;
        sf::Vector2f mSpawnLocation;

        int mSpawnAmount;
        int mCurrentSpawnCount;

        TimerHandle mSpawnTimerHandle;
    };
}