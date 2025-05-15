#include "framework/Application.h"

namespace ly
{
    Application::Application()
        :mWindow{ sf::VideoMode(sf::Vector2u(1024,1440)), "Light Years" }
    { }

    void Application::Run()
    {
        while (mWindow.isOpen())
        {
            while (const std::optional windowEvent = mWindow.pollEvent())
            {
                if (windowEvent->is<sf::Event::Closed>()) {
                    mWindow.close();
                }
            }
        }
    }
}