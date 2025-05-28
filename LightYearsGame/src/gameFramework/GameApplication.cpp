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
        newWorld.lock()->SpawnActor<Actor>();
        testPlayer = newWorld.lock()->SpawnActor<PlayerSpaceship>();
        testPlayer.lock()->SetActorLocation(sf::Vector2f(512.f, 770.f));
        testPlayer.lock()->SetActorRotation(0.f);
    }

    void GameApplication::Tick(float deltaTime)
    {
    }
}
