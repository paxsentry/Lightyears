#include "widgets/HUD.h"

namespace ly
{
    HUD::HUD()
        : mAlreadyInit{ false }
    {}

    void HUD::NativeInit(const sf::RenderWindow& renderWindow)
    {
        if (!mAlreadyInit)
        {
            mAlreadyInit = true;
            Init(renderWindow);
        }
    }

    bool HUD::HandleEvent(const sf::Event& event)
    {
        return false;
    }

    void HUD::Init(const sf::RenderWindow& renderWindow)
    {}

    void HUD::Tick(float deltaTime)
    {}
}