#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "gameplay/GameStage.h"
#include "widgets/HUD.h"

namespace ly
{
    World::World(Application* owningApp)
        :mOwningApp{ owningApp },
        mBeginPlay{ false },
        mActors{},
        mPendingActors{},
        mGameStages{},
        mCurrentStage{ mGameStages.end() }
    {}

    void World::BeginPlayInternal()
    {
        if (!mBeginPlay)
        {
            mBeginPlay = true;
            BeginPlay();
            InitGameStages();
            StartStages();
        }
    }

    World::~World()
    {}

    void World::BeginPlay()
    {}

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
            iter->get()->TickInternal(deltaTime);
            ++iter;
        }

        if (mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->TickStage(deltaTime);
        }

        Tick(deltaTime);

        if (mHUD && !mHUD->HasInit())
        {
            mHUD->NativeInit(mOwningApp->GetRenderWindow());
        }
    }

    void World::Tick(float deltaTime)
    {}

    void World::RenderHUD(sf::RenderWindow& window)
    {
        if (mHUD)
        {
            mHUD->Draw(window);
        }
    }

    void World::InitGameStages()
    {}

    void World::NextGameStage()
    {
        mCurrentStage = mGameStages.erase(mCurrentStage);

        if (mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->StartStage();
            mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
        }
        else
        {
            AllGameStageFinished();
        }
    }

    void World::AllGameStageFinished()
    {
        LOG("All stages finished");
    }

    void World::StartStages()
    {
        mCurrentStage = mGameStages.begin();
        mCurrentStage->get()->StartStage();
        mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
    }

    void World::Render(sf::RenderWindow& window)
    {
        for (auto& actor : mActors)
        {
            actor->Render(window);
        }

        RenderHUD(window);
    }

    sf::Vector2u World::GetWindowSize() const
    {
        return mOwningApp->GetWindowSize();
    }

    void World::CleanCycle()
    {
        for (auto iter = mActors.begin(); iter != mActors.end();)
        {
            if (iter->get()->IsPendingDestruction())
            {
                iter = mActors.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    void World::AddStage(const shared<GameStage>& newStage)
    {
        mGameStages.push_back(newStage);
    }

    bool World::DispatchEvent(const std::optional<sf::Event>& event)
    {
        if (mHUD)
        {
            return mHUD->HandleEvent(event);
        }

        return false;
    }
}
