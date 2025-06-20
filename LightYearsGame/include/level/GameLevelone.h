#pragma once
#include "framework/World.h"

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
        void TimerCallback();
        unsigned int timerindextest;
    };
}