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
        weak<PlayerSpaceship> testPlayer;
    };
}