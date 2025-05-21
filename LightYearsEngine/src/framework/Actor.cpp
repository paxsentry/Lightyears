#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
    Actor::Actor(World* owningWorld)
        :mOwningWorld{ owningWorld },
        mHasBeganPlay{ false }
    {
    }

    Actor::~Actor()
    {
        LOG("Actor destroyed");
    }

    void  Actor::BeginPlayInternal()
    {
        if (!mHasBeganPlay)
        {
            mHasBeganPlay = true;
            BeginPlay();
        }
    }

    void Actor::BeginPlay()
    {
        LOG("Actor begin play");
    }

    void Actor::Tick(float deltaTime)
    {
        LOG("Actor ticking at FPS: %f", 1.f / deltaTime);
    }
}