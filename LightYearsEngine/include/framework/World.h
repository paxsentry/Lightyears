#pragma once
#include "framework/Core.h"
#include "framework/Object.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class Application;
    class Actor;
    class GameStage;
    class HUD;

    class World : public Object
    {
    public:
        World(Application* owningApp);

        void TickInternal(float deltaTime);
        void BeginPlayInternal();
        void Render(sf::RenderWindow& window);

        virtual ~World();

        template<typename ActorType, typename...Args>
        weak<ActorType> SpawnActor(Args... args);

        template<typename HUDType, typename...Args>
        weak<HUDType> SpawnHUD(Args... args);

        sf::Vector2u GetWindowSize() const;
        void CleanCycle();
        void AddStage(const shared<GameStage>& newStage);
        bool DispatchEvent(const std::optional<sf::Event>& event);

    private:
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
        void RenderHUD(sf::RenderWindow& window);

        Application* mOwningApp;
        bool mBeginPlay;

        List<shared<Actor>> mActors;
        List<shared<Actor>> mPendingActors;
        List<shared<GameStage>> mGameStages;
        List<shared<GameStage>>::iterator mCurrentStage;
        shared<HUD> mHUD;

        virtual void InitGameStages();
        void NextGameStage();
        virtual void AllGameStageFinished();
        void StartStages();
    };

    template<typename ActorType, typename...Args>
    weak<ActorType> World::SpawnActor(Args...args)
    {
        shared<ActorType> newActor{ new ActorType(this, args...) };
        mPendingActors.push_back(newActor);

        return newActor;
    }

    template<typename HUDType, typename ...Args>
    inline weak<HUDType> World::SpawnHUD(Args ...args)
    {
        shared<HUDType> newHUD{ new HUDType(args...) };
        mHUD = newHUD;

        return newHUD;
    }
}