#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetsManager.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, std::uint32_t style)
        :mWindow{ sf::VideoMode(sf::Vector2u(windowWidth,windowHeight)), title, style },
        mTargetFrameRate{ 60.f },
        mTickClock{ },
        currentWorld{ nullptr },
        mCleanCycleClock{},
        mCleanCycleInterval{2.f}
    {
    }

    void Application::Run()
    {
        mTickClock.restart();
        float accumulatedTime = 0.f;
        float targetDeltaTime = 1.f / mTargetFrameRate;

        while (mWindow.isOpen())
        {
            while (const std::optional windowEvent = mWindow.pollEvent())
            {
                if (windowEvent->is<sf::Event::Closed>()) {
                    mWindow.close();
                }
            }

            float frameDeltaTime = mTickClock.restart().asSeconds();
            accumulatedTime += frameDeltaTime;
            while (accumulatedTime > targetDeltaTime)
            {
                accumulatedTime -= targetDeltaTime;
                TickInternal(targetDeltaTime);
                RenderInternal();
            }

            // The actual framerate
            // LOG("ticking at the set FPS: %f", 1.f / frameDeltaTime);
        }
    }

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);

        if (currentWorld)
        {
            currentWorld->TickInternal(deltaTime);
        }

        PhysicsSystem::Get().Step(deltaTime);

        if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
        {
            mCleanCycleClock.restart();
            AssetsManager::Get().CleanCycle();

            if (currentWorld)
            {
                currentWorld->CleanCycle();
            }
        }
    }

    void Application::RenderInternal()
    {
        mWindow.clear();

        Render();

        mWindow.display();
    }

    void Application::Render()
    {
        if (currentWorld) {
            currentWorld->Render(mWindow);
       }
    }

    void Application::Tick(float deltaTime)
    {
        printf("ticking at the set FPS: %f\n", 1.f / deltaTime);
    }

    sf::Vector2u Application::GetWindowSize() const
    {
        return mWindow.getSize();
    }
}