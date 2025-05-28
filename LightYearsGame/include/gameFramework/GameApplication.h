#pragma once

#include <framework/Application.h>
#include <framework/Core.h>

namespace ly
{
    class Actor;
    class Spaceship;
    class PlayerSpaceship;

    class GameApplication : public Application 
    {
    public:
        GameApplication();
        virtual void Tick(float deltaTime);
    private:
        float mCounter;
        weak<PlayerSpaceship> testPlayer;
    };
}