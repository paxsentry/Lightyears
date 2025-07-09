#pragma once
#include "spaceship/Spaceship.h"
#include "framework/TimerManager.h"

namespace ly
{
    class Shooter;

    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip2_blue.png");

        virtual void Tick(float deltaTime) override;
        void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
        float GetSpeed() const { return mSpeed; }
        virtual void Shoot() override;
        void SetShooter(unique<Shooter>&& newShooter);
        virtual void ApplyDamage(float amount) override;
        virtual void BeginPlay() override;

    private:
        void HandleInput();
        void ConsumeInput(float deltaTime);
        void NormaliseInput();
        void ClampInputOnEdge();
        void DisableInvulenrability();
        void UpdateInvulnerable(float deltaTime);

        sf::Vector2f mMoveInput;
        float mSpeed;

        unique<Shooter> mShooter;

        float mInvulnerableTime;
        TimerHandle mInvulnerableTimerHandle;
        bool mInvulnerable;

        float mInvulnerableFlashInterval;
        float mInvulnerableFlashTimer;
        float mInvulnerableFlashDirection;
    };
}