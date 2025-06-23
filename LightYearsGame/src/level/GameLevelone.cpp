#include "enemy/Vanguard.h"
#include "framework/Actor.h"
#include "framework/AssetsManager.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "gameplay/GameStage.h"
#include "level/GameLevelone.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    GameLevelone::GameLevelone(Application* application)
        :World(application)
    {
        testPlayer = SpawnActor<PlayerSpaceship>();
        testPlayer.lock()->SetActorLocation(sf::Vector2f(512.f, 770.f));
        testPlayer.lock()->SetActorRotation(0.f);
        //testPlayer.lock()->DrawDebugLines();

        weak<Vanguard> enemyOne = SpawnActor<Vanguard>();
        enemyOne.lock()->SetActorLocation(sf::Vector2f(256.f, 500.f));
        // enemyOne.lock()->DrawDebugLines();
    }

    void GameLevelone::BeginPlay()
    {
        timerindextest = TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelone::TimerCallback, 3, true);
    }

    void GameLevelone::TimerCallback()
    {
        LOG("TimerCallback");
        TimerManager::Get().ClearTimer(timerindextest);
    }

    void GameLevelone::InitGameStages()
    {
        AddStage(shared<GameStage> {new GameStage{ this }});
    }
}