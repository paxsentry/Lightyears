#include "framework/Application.h"
#include "framework/AssetsManager.h"
#include "framework/Core.h"
#include "framework/PhysicsSystem.h"
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly
{
    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, std::uint32_t style)
        :mWindow{ sf::VideoMode(sf::Vector2u(windowWidth,windowHeight)), title, style },
        mTargetFrameRate{ 60.f },
        mTickClock{ },
        mCurrentWorld{ nullptr },
        mCleanCycleClock{},
        mCleanCycleInterval{ 2.f }
    {}

    void Application::Run()
    {
        mTickClock.restart();
        float accumulatedTime = 0.f;
        float targetDeltaTime = 1.f / mTargetFrameRate;

        while (mWindow.isOpen())
        {
            //sf::Event windowEvent;
            while (const std::optional windowEvent = mWindow.pollEvent())
            {
                if (windowEvent->is<sf::Event::Closed>())
                {
                    QuitApplication();
                }
                else
                {
                    DispatchEvent(windowEvent.value());
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

    void Application::QuitApplication()
    {
        mWindow.close();
    }

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);

        if (mCurrentWorld)
        {
            mCurrentWorld->TickInternal(deltaTime);
        }

        TimerManager::Get().UpdateTimer(deltaTime);

        PhysicsSystem::Get().Step(deltaTime);

        if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
        {
            mCleanCycleClock.restart();
            AssetsManager::Get().CleanCycle();

            if (mCurrentWorld)
            {
                mCurrentWorld->CleanCycle();
            }
        }

        if (mPendingWorld && mPendingWorld != mCurrentWorld)
        {
            mCurrentWorld = mPendingWorld;
            mCurrentWorld->BeginPlayInternal();
        }
    }

    void Application::RenderInternal()
    {
        mWindow.clear();

        Render();

        mWindow.display();
    }

    bool Application::DispatchEvent(const sf::Event& event)
    {
        if (mCurrentWorld)
        {
            return mCurrentWorld->DispatchEvent(event);
        }

        return false;
    }

    void Application::Render()
    {
        if (mCurrentWorld)
        {
            mCurrentWorld->Render(mWindow);
        }
    }

    void Application::Tick(float deltaTime)
    {}

    sf::Vector2u Application::GetWindowSize() const
    {
        return mWindow.getSize();
    }
}