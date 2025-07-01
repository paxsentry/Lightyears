#pragma once
#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"

namespace ly
{
    class GameplayHUD : public HUD
    {
    public:
        GameplayHUD();
        virtual void Draw(sf::RenderWindow& window) override;
        virtual void Tick(float deltaTime) override;

    private:
        TextWidget mFpsText;
        ValueGauge mPlayerHealthBar;

        virtual void Init(const sf::RenderWindow& window) override;
    };
}