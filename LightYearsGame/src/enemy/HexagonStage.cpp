#include "enemy/HexagonStage.h"
#include "framework/World.h"
#include "enemy/Hexagon.h"

namespace ly
{
    HexagonStage::HexagonStage(World* world)
        :GameStage{ world },
        mSpawnInterval{ 1.5f },
        mSideSpawnOffset{ 80.f },
        mSpawnGroupsAmount{ 1 },
        mCurrentSpawnCount{ 0 },
        mMidSpawnLocation{ world->GetWindowSize().x / 2.f, -100.f },
        mLeftSpawnLocation{ world->GetWindowSize().x / 2.f - mSideSpawnOffset, -100.f - mSideSpawnOffset },
        mRightSpawnLocation{ world->GetWindowSize().x / 2.f + mSideSpawnOffset, -100.f - mSideSpawnOffset }
    {}

    void HexagonStage::StartStage()
    {
        mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &HexagonStage::SpawnHexagons, mSpawnInterval, true);
    }

    void HexagonStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(mSpawnTimer);
    }

    void HexagonStage::SpawnHexagons()
    {
        weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
        newHexagon.lock()->SetActorLocation(mMidSpawnLocation);

        newHexagon = GetWorld()->SpawnActor<Hexagon>();
        newHexagon.lock()->SetActorLocation(mLeftSpawnLocation);

        newHexagon = GetWorld()->SpawnActor<Hexagon>();
        newHexagon.lock()->SetActorLocation(mRightSpawnLocation);

        if (++mCurrentSpawnCount == mSpawnGroupsAmount)
        {
            FinishStage();
        }
    }
}