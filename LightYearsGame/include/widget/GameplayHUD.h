#pragma once
#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"
#include "widgets/ImageWidget.h"

namespace ly
{
    class Actor;

    class GameplayHUD : public HUD
    {
    public:
        GameplayHUD();
        virtual void Draw(sf::RenderWindow& window) override;
        virtual void Tick(float deltaTime) override;

    private:
        TextWidget mFpsText;
        ValueGauge mPlayerHealthBar;
        ImageWidget mPlayerLifeIcon;
        TextWidget mPlayerLifeText;

        virtual void Init(const sf::RenderWindow& window) override;
        void PlayerHealthUpdated(float amount, float currentHealth, float maxHealth);
        void RefreshHealthBar();
        void ConnectPlayerLifeCount();
        void PlayerLifeCountUpdated(int amount);
        void PlayerSpaceshipDestroyed(Actor* actor);

        sf::Color mHealthyHealthBarColor;
        sf::Color mCriticalHealthBarColor;
        float mCriticalThreshold;

        float mWidgetSpacing;
    };
}