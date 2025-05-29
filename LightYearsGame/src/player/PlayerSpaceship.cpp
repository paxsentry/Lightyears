#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
        :Spaceship{ owningWorld, path },
        mMoveInput{},
        mSpeed{ 200.f },
        mShooter { new BulletShooter{this} }
    {
    }

    void PlayerSpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        HandleInput();
        ConsumeInput(deltaTime);
    }

    void PlayerSpaceship::Shoot()
    {
        if (mShooter)
        {
            mShooter->Shoot();
        }
    }

    void PlayerSpaceship::HandleInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
        {
            mMoveInput.y = -1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            mMoveInput.y = 1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            mMoveInput.x = -1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            mMoveInput.x = 1.f;
        }

        ClampInputOnEdge();
        NormaliseInput();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            Shoot();
        }
    }

    void PlayerSpaceship::ConsumeInput(float deltaTime)
    {
        SetVelocity(mMoveInput * mSpeed);
        mMoveInput.x = mMoveInput.y = 0;
    }

    void PlayerSpaceship::NormaliseInput()
    {
        Normalise(mMoveInput);
    }

    void PlayerSpaceship::ClampInputOnEdge()
    {
        sf::Vector2f actorLocation = GetActorLocation();

        if (actorLocation.x < 0 && mMoveInput.x == -1.f)
        {
            mMoveInput.x = 0.f;
        }

        if (actorLocation.x > GetWindowSize().x && mMoveInput.x == 1.f)
        {
            mMoveInput.x = 0.f;
        }

        if (actorLocation.y < 0 && mMoveInput.y == -1.f)
        {
            mMoveInput.y = 0.f;
        }

        if (actorLocation.y > GetWindowSize().y && mMoveInput.y == 1.f)
        {
            mMoveInput.y = 0.f;
        }
    }
}