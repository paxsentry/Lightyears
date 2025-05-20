#pragma once

namespace ly
{
    class Application;

    class World {
    public:
        World(Application* owningApp);
        
        void TickInternal(float deltaTime);
        void BeginPlayInternal();

        virtual ~World();

    private:
        void BeginPlay();
        void Tick(float deltaTime);

        Application* mOwningApp;
        bool mBeginPlay;
    };
}