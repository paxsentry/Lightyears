#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly
{
    class PlayerSpaceship;

    class GameLevelone : public World
    {
    public:
        GameLevelone(Application* application);

    private:
        virtual void BeginPlay() override;
        weak<PlayerSpaceship> testPlayer;
        virtual void InitGameStages() override;
    };
}