#pragma once
#include "framework/Core.h"
#include "framework/Object.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class Application;
    class Actor;
    class GameStage;

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

        sf::Vector2u GetWindowSize() const;
        void CleanCycle();
        void AddStage(const shared<GameStage>& newStage);

    private:
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);

        Application* mOwningApp;
        bool mBeginPlay;

        List<shared<Actor>> mActors;
        List<shared<Actor>> mPendingActors;
        List<shared<GameStage>> mGameStages;
        List<shared<GameStage>>::iterator mCurrentStage;

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
}