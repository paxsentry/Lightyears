#pragma once
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class ChaosStage : public GameStage
    {
    public:
        ChaosStage(World* world);

        virtual void StartStage() override;

    private:
        virtual void StageFinished() override;
        void SpawnVanguard();
        void SpawnTwinBlade();
        void SpawnHexagon();
        void SpawnUFO();

        void IncreaseDifficulty();
        void StageDurationReached();

        sf::Vector2f GetRandomSpawnLocationTop() const;
        sf::Vector2f GetRandomSpawnLocationSide() const;

        float mSpawnInterval;
        float mMinSpawnInterval;
        float mSpawnIntervalDecrement;
        float mSpawnIntervalDecrementInterval;

        float mStageDuration;

        TimerHandle mDifficultyTimerHandle;
        TimerHandle mSpawnTimer;
    };
}