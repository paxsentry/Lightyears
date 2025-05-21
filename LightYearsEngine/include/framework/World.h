#pragma once
#include "framework/Core.h"

namespace ly
{
    class Application;
    class Actor;

    class World {
    public:
        World(Application* owningApp);

        void TickInternal(float deltaTime);
        void BeginPlayInternal();

        virtual ~World();

        template<typename ActorType>
        weak<ActorType> SpawnActor();

    private:
        void BeginPlay();
        void Tick(float deltaTime);

        Application* mOwningApp;
        bool mBeginPlay;

        List<shared<Actor>> mActors;
        List<shared<Actor>> mPendingActors;
    };

    template<typename ActorType>
    weak<ActorType> World::SpawnActor()
    {
        shared<ActorType> newActor{ new ActorType{this} };
        mPendingActors.push_back(newActor);

        return newActor;
    }
}