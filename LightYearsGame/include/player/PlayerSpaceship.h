#pragma once
#include "spaceship/Spaceship.h"

namespace ly
{
    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip2_blue.png");

        virtual void Tick(float deltaTime) override;
        void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
        float GetSpeed() { return mSpeed; }

    private:
        void HandleInput();
        void ConsumeInput(float deltaTime);
        void NormaliseInput();

        sf::Vector2f mMoveInput;
        float mSpeed;
    };
}