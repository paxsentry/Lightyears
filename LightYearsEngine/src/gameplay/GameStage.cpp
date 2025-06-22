#include "framework/Core.h"
#include "gameplay/GameStage.h"

namespace ly
{
    GameStage::GameStage(World* world)
        : mWorld{ world },
        mStageFinished{ false }
    {}

    void GameStage::StartStage()
    {
        LOG("Stage started");
    }

    void GameStage::TickStage(float deltaTime)
    {
        LOG("Stage ticking");
    }

    void GameStage::FinishStage()
    {
        onStageFinished.BroadCast();
        mStageFinished = true;
        StageFinished();
    }

    void GameStage::StageFinished()
    {
        LOG("Stage finished");
    }
}