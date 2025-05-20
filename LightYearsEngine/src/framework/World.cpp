#include "framework/World.h"
#include "framework/Core.h"

namespace ly
{
    World::World(Application* owningApp)
        :mOwningApp{ owningApp },
        mBeginPlay{ false }
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
        LOG("World is ticking at FPS: %f", 1.f / deltaTime);
        // Tick(deltaTime);
    }
}