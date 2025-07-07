#pragma once
#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"
#include "widgets/ImageWidget.h"
#include "widgets/ButtonWidget.h"

namespace ly
{
    class Actor;

    class GameplayHUD : public HUD
    {
    public:
        GameplayHUD();
        virtual void Draw(sf::RenderWindow& window) override;
        virtual void Tick(float deltaTime) override;
        virtual bool HandleEvent(const sf::Event& event) override;

    private:
        TextWidget mFpsText;
        ValueGauge mPlayerHealthBar;
        ImageWidget mPlayerLifeIcon;
        TextWidget mPlayerLifeText;
        ImageWidget mPlayerScoreIcon;
        TextWidget mPlayerScoreText;

        ButtonWidget mTestButton;

        virtual void Init(const sf::RenderWindow& window) override;
        void PlayerHealthUpdated(float amount, float currentHealth, float maxHealth);
        void RefreshHealthBar();
        void ConnectPlayerStats();
        void PlayerLifeCountUpdated(int amount);
        void PlayerScoreUpdated(int amount);
        void PlayerSpaceshipDestroyed(Actor* actor);

        sf::Color mHealthyHealthBarColor;
        sf::Color mCriticalHealthBarColor;
        float mCriticalThreshold;

        float mWidgetSpacing;
        void TestButtonclicked();
    };
}