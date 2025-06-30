#pragma once
#include "framework/Object.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class HUD : public Object
    {
    public:
        virtual void Draw(sf::RenderWindow& renderWindow) =0;
        void NativeInit(const sf::RenderWindow& renderWindow);
        bool HasInit() const { return mAlreadyInit; }
        virtual bool HandleEvent(const std::optional<sf::Event>& event);

    protected:
        HUD();

    private:
        bool mAlreadyInit;
        virtual void Init(const sf::RenderWindow& renderWindow);
    };
}