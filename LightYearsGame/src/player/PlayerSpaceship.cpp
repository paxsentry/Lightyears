#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"

namespace ly
{
    PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
        :Spaceship{ owningWorld, path },
        mMoveInput{},
        mSpeed{200.f}
    {
    }

    void PlayerSpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        HandleInput();
        ConsumeInput(deltaTime);
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
    }

    void PlayerSpaceship::ConsumeInput(float deltaTime)
    {
        SetVelocity(mMoveInput * mSpeed);
        mMoveInput.x = mMoveInput.y = 0;
    }
}