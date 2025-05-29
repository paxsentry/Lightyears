#pragma once
#include "spaceship/Spaceship.h"

namespace ly
{
    class BulletShooter;

    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip2_blue.png");

        virtual void Tick(float deltaTime) override;
        void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
        float GetSpeed() const { return mSpeed; }
        virtual void Shoot() override;

    private:
        void HandleInput();
        void ConsumeInput(float deltaTime);
        void NormaliseInput();
        void ClampInputOnEdge();

        sf::Vector2f mMoveInput;
        float mSpeed;

        unique<BulletShooter> mShooter;
    };
}