#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly
{
    class PlayerSpaceship;

    class GameLevelOne : public World
    {
    public:
        GameLevelOne(Application* application);

    private:
        virtual void BeginPlay() override;
        weak<PlayerSpaceship> mPlayerSpaceship;
        virtual void InitGameStages() override;
        void PlayerSpaceshipDestroyed(Actor* playerSpaceship);
        void GameOver();
    };
}