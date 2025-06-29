#pragma once
#include "framework/Object.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class HUD : public Object
    {
    public:
        virtual void Draw(sf::RenderWindow& renderWindow) =0;
        void NativeInit(sf::RenderWindow& renderWindow);
        bool HasInit() const { return mAlreadyInit; }
        virtual bool HandleEvent(const sf::Event& event);

    protected:
        HUD();

    private:
        bool mAlreadyInit;
        virtual void Init(sf::RenderWindow& renderWindow);
    };
}