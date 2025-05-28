#include "framework/Actor.h"
#include "framework/World.h"
#include "gameFramework/GameApplication.h"
#include "config.h"
#include "spaceship/Spaceship.h"

ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
        :Application{ 1024, 1440,"Light years", sf::Style::Titlebar | sf::Style::Close }
    {
        weak<World> newWorld = LoadWorld<World>();
        newWorld.lock()->SpawnActor<Actor>();
       testPlayer = newWorld.lock()->SpawnActor<Spaceship>();
        testPlayer.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip2_blue.png");
        testPlayer.lock()->SetActorLocation(sf::Vector2f(512.f, 770.f));
        testPlayer.lock()->SetActorRotation(0.f);
        testPlayer.lock()->SetVelocity(sf::Vector2f(0.f, -150.f));
        mCounter = 0;
    }

    void GameApplication::Tick(float deltaTime)
    {
    }
}
