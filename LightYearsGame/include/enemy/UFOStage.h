#pragma once
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class UFOStage : public GameStage
    {
    public:
        UFOStage(World* world);
        virtual void StartStage() override;

    private:
        virtual void StageFinished() override;
        void SpawnUFO();
        sf::Vector2f GetRandomSpawnLocation() const;

        int mSpawnAmount;
        float mSpawnInterval;
        int mCurrentSpawnAmount;
        float mUFOSpeed;

        TimerHandle mSpawnTimer;
    };
}