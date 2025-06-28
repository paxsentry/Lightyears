#pragma once
#include "framework/Delegate.h"
#include "framework/Object.h"

namespace ly
{
    class PlayerSpaceship;
    class World;

    class Player : public Object
    {
    public:
        Player();

        weak<PlayerSpaceship> SpawnSpaceship(World* world);
        const weak<PlayerSpaceship> GetCurrentSpaceship() const { return mCurrentPlayerSpaceship; }

        void AddLifeCount(unsigned int count);
        void AddScore(unsigned int score);
        int GetLifeCount() const { return mLifeCount; }
        int GetScore() const { return mScore; }

        Delegate<int> onLifeChange;
        Delegate<int> onScoreChange;
        Delegate<> onLifeExhausted;

    private:
        unsigned int mLifeCount;
        unsigned int mScore;
        weak<PlayerSpaceship> mCurrentPlayerSpaceship;
    };
}