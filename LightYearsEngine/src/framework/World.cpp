#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
    World::World(Application* owningApp)
        :mOwningApp{ owningApp },
        mBeginPlay{ false },
        mActors{},
        mPendingActors{}
    {
    }

    void World::BeginPlayInternal()
    {
        if (!mBeginPlay)
        {
            mBeginPlay = true;
            BeginPlay();
        }
    }

    World::~World()
    {
    }

    void World::BeginPlay()
    {
        LOG("Begin play");
    }

    void World::TickInternal(float deltaTime)
    {
        for (shared<Actor> actor : mPendingActors)
        {
            mActors.push_back(actor);
            actor->BeginPlay();
        }

        mPendingActors.clear();

        for (auto iter = mActors.begin(); iter != mActors.end();)
        {
            if (iter->get()->IsPendingDestruction()) {
                iter = mActors.erase(iter);
            }
            else {
                iter->get()->Tick(deltaTime);
                ++iter;
            }
        }

        Tick(deltaTime);
    }

    void World::Tick(float deltaTime)
    {
        LOG("World is ticking at FPS: %f", 1.f / deltaTime);
    }
}
