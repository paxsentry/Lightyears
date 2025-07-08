#pragma once
#include "widgets/HUD.h"
#include "widgets/ButtonWidget.h"
#include "widgets/TextWidget.h"

namespace ly
{
    class MainMenuHUD : public HUD
    {
    public:
        MainMenuHUD();
        
        virtual void Draw(sf::RenderWindow& window) override;
        virtual bool HandleEvent(const sf::Event& event) override;

        Delegate<> onStartButtonClicked;
        Delegate<> onQuitButtonClicked;

    private:
        virtual void Init(const sf::RenderWindow& window) override;

        TextWidget mTitleText;
        ButtonWidget mStartButton;
        ButtonWidget mQuitButton;

        void StartButtonClicked();
        void QuitButtonClicked();
    };
}