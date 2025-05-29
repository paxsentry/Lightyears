#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/Application.h"

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
    }

    void World::TickInternal(float deltaTime)
    {
        for (shared<Actor> actor : mPendingActors)
        {
            mActors.push_back(actor);
            actor->BeginPlayInternal();
        }

        mPendingActors.clear();

        for (auto iter = mActors.begin(); iter != mActors.end();)
        {
            if (iter->get()->IsPendingDestruction()) {
                iter = mActors.erase(iter);
            }
            else {
                iter->get()->TickInternal(deltaTime);
                ++iter;
            }
        }

        Tick(deltaTime);
    }

    void World::Tick(float deltaTime)
    {
    }

    void World::Render(sf::RenderWindow& window)
    {
        for (auto& actor : mActors)
        {
            actor->Render(window);
        }
    }

    sf::Vector2u World::GetWindowSize() const
    {
        return mOwningApp->GetWindowSize();
    }
}
