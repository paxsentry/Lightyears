#include "framework/World.h"
#include "player/Player.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    Player::Player()
        :mLifeCount{ 3 },
        mScore{ 0 },
        mCurrentPlayerSpaceship{}
    {}

    weak<PlayerSpaceship> Player::SpawnSpaceship(World* world)
    {
        if (mLifeCount > 0)
        {
            --mLifeCount;
            auto windowSize = world->GetWindowSize();

            mCurrentPlayerSpaceship = world->SpawnActor<PlayerSpaceship>();
            mCurrentPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(windowSize.x / 2.f, windowSize.y - 100.f));
            mCurrentPlayerSpaceship.lock()->SetActorRotation(0.f);

            onLifeChange.BroadCast(mLifeCount);
        }
        else
        {
            onLifeExhausted.BroadCast();
        }
    }

    void Player::AddLifeCount(unsigned int count)
    {
        if (count > 0)
        {
            mLifeCount += count;
            onLifeChange.BroadCast(mLifeCount);
        }
    }

    void Player::AddScore(unsigned int score)
    {
        if (score > 0)
        {
            mScore += score;
            onScoreChange.BroadCast(mScore);
        }
    }
}