#include "enemy/UFO.h"
#include "enemy/UFOStage.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
    UFOStage::UFOStage(World* world)
        : GameStage{ world },
        mSpawnInterval{ 4.f },
        mSpawnAmount{ 10 },
        mCurrentSpawnAmount{ 0 },
        mUFOSpeed{ 200.f }
    {}

    void UFOStage::StartStage()
    {
        mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, mSpawnInterval, true);
    }

    void UFOStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(mSpawnTimer);
    }

    sf::Vector2f UFOStage::GetRandomSpawnLocation() const
    {
        auto windowSize = GetWorld()->GetWindowSize();

        float spawnLeft = RandomRange(-1, 1);
        float spawnLocationX = 0;
        if (spawnLeft < 0)
        {
            spawnLocationX = windowSize.x + 100.f;
        }
        else
        {
            spawnLocationX = -100.f;
        }

        float spawnLocationY = RandomRange(0, windowSize.y);

        return sf::Vector2f{ spawnLocationX, spawnLocationY };
    }

    void UFOStage::SpawnUFO()
    {
        sf::Vector2f spawnLoc = GetRandomSpawnLocation();
        auto windowSize = GetWorld()->GetWindowSize();
        sf::Vector2f center{ windowSize.x / 2.f, windowSize.y / 2.f };
        sf::Vector2f spawnLocationToCenter{ center.x - spawnLoc.x, center.y - spawnLoc.y };
        Normalise(spawnLocationToCenter);

        sf::Vector2f velocity = spawnLocationToCenter * mUFOSpeed;

        weak<UFO> newUfo = GetWorld()->SpawnActor<UFO>(velocity);
        newUfo.lock()->SetActorLocation(spawnLoc);

        if (++mCurrentSpawnAmount == mSpawnAmount)
        {
            FinishStage();
        }
    }
}