#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
    Application::Application()
        :mWindow{ sf::VideoMode(sf::Vector2u(1024,1440)), "Light Years" },
        mTargetFrameRate{ 60.f },
        mTickClock{ },
        currentWorld{ nullptr }
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
    }

    void Application::RenderInternal()
    {
        mWindow.clear();

        Render();

        mWindow.display();
    }

    void Application::Render()
    {
        sf::RectangleShape rect{ sf::Vector2f{200,200} };
        rect.setFillColor(sf::Color::Green);
        rect.setPosition(sf::Vector2f(mWindow.getSize().x / 2.f - 100, mWindow.getSize().y / 2.f - 100));
        mWindow.draw(rect);
    }

    void Application::Tick(float deltaTime)
    {
        printf("ticking at the set FPS: %f\n", 1.f / deltaTime);
    }
}