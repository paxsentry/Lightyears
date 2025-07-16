#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly
{
    class PlayerSpaceship;
    class GameplayHUD;

    class GameLevelOne : public World
    {
    public:
        GameLevelOne(Application* application);

    private:
        virtual void BeginPlay() override;
        virtual void InitGameStages() override;
        virtual void AllGameStageFinished() override;

        weak<PlayerSpaceship> mPlayerSpaceship;
        weak<GameplayHUD> mGameplayHUD;
        void PlayerSpaceshipDestroyed(Actor* playerSpaceship);
        void GameOver();
        void QuitGame();
        void RestartGame();
    };
}