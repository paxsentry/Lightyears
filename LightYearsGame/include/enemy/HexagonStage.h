#pragma once
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class HexagonStage : public GameStage
    {
    public:
        HexagonStage(World* world);

        virtual void StartStage() override;

    private:
        virtual void StageFinished() override;
        void SpawnHexagons();

        float mSpawnInterval;
        float mSideSpawnOffset;
        int mSpawnGroupsAmount;
        int mCurrentSpawnCount;

        sf::Vector2f mMidSpawnLocation;
        sf::Vector2f mLeftSpawnLocation;
        sf::Vector2f mRightSpawnLocation;

        TimerHandle mSpawnTimer;
    };
}