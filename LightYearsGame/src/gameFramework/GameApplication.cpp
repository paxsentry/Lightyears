#include "framework/Actor.h"
#include "framework/World.h"
#include "gameFramework/GameApplication.h"

ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
    {
        weak<World> newWorld = LoadWorld<World>();
        newWorld.lock()->SpawnActor<Actor>();
        mActorToDestroy = newWorld.lock()->SpawnActor<Actor>();
        mCounter = 0;
    }

    void GameApplication::Tick(float deltaTime) {
        mCounter += deltaTime;
        if (mCounter > 2.f) {
            if (!mActorToDestroy.expired()) {
                mActorToDestroy.lock()->Destroy();
            }
        }
    }
}
