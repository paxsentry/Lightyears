#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class Application;
    class Actor;

    class World {
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

    private:
        void BeginPlay();
        void Tick(float deltaTime);

        Application* mOwningApp;
        bool mBeginPlay;

        List<shared<Actor>> mActors;
        List<shared<Actor>> mPendingActors;
    };

    template<typename ActorType, typename...Args>
    weak<ActorType> World::SpawnActor(Args...args)
    {
        shared<ActorType> newActor{ new ActorType(this, args...) };
        mPendingActors.push_back(newActor);

        return newActor;
    }
}