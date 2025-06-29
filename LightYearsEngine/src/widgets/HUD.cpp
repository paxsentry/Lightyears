#include "widgets/HUD.h"

namespace ly
{
    HUD::HUD()
        : mAlreadyInit{ false }
    {}

    void HUD::NativeInit(sf::RenderWindow& renderWindow)
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

    void HUD::Init(sf::RenderWindow & renderWindow)
    {
    
    }
}