#include "framework/Actor.h"
#include "framework/World.h"
#include "gameFramework/GameApplication.h"
#include "config.h"
#include "player/PlayerSpaceship.h"
#include <framework/AssetsManager.h>

ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
        :Application{ 1024, 1440,"Light years", sf::Style::Titlebar | sf::Style::Close }
    {
        AssetsManager::Get().SetAssetsRootDirectory(GetResourceDir());

        weak<World> newWorld = LoadWorld<World>();
        testPlayer = newWorld.lock()->SpawnActor<PlayerSpaceship>();
        testPlayer.lock()->SetActorLocation(sf::Vector2f(512.f, 770.f));
        testPlayer.lock()->SetActorRotation(0.f);
        testPlayer.lock()->DrawDebugLines();

        weak<Spaceship> enemyOne = newWorld.lock()->SpawnActor<Spaceship>();
        enemyOne.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip2_red.png");
        enemyOne.lock()->SetActorLocation(sf::Vector2f(256.f, 500.f));
        enemyOne.lock()->SetActorRotation(180.f);
        enemyOne.lock()->DrawDebugLines();
    }

    void GameApplication::Tick(float deltaTime)
    {
    }
}
