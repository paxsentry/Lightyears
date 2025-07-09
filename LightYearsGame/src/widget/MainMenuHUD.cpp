#include "widget/MainMenuHUD.h"
#include <iostream>

namespace ly
{
    MainMenuHUD::MainMenuHUD()
        : mTitleText{ "Light Years" },
        mStartButton{ "Start" },
        mQuitButton{ "Quit" }
    {
        mTitleText.SetTextSize(50);
        mStartButton.SetButtonTextSize(25);
        mQuitButton.SetButtonTextSize(25);
    }

    void MainMenuHUD::Draw(sf::RenderWindow& window)
    {
        mTitleText.NativeDraw(window);
        mStartButton.NativeDraw(window);
        mQuitButton.NativeDraw(window);
    }

    bool MainMenuHUD::HandleEvent(const sf::Event& event)
    {
        bool handled = false;
        handled |= mStartButton.HandleEvent(event);
        handled |= mQuitButton.HandleEvent(event);
        handled |= HUD::HandleEvent(event);

        return handled;
    }

    void MainMenuHUD::Init(const sf::RenderWindow& window)
    {
        sf::Vector2u windowSize = window.getSize();

        mTitleText.SetWidgetLocation({ windowSize.x / 2.f - mTitleText.GetBound().size.x / 2.f , 100.f});
        mStartButton.SetWidgetLocation({ windowSize.x / 2.f - mStartButton.GetBound().size.x / 2.f, windowSize.y / 2.f});
        mQuitButton.SetWidgetLocation(mStartButton.GetWidgetLocation() + sf::Vector2f{0.f, 50.f });

        mStartButton.onButtonClick.BindAction(GetWeakRef(), &MainMenuHUD::StartButtonClicked);
        mQuitButton.onButtonClick.BindAction(GetWeakRef(), &MainMenuHUD::QuitButtonClicked);
    }

    void MainMenuHUD::StartButtonClicked()
    {
        onStartButtonClicked.BroadCast();
    }

    void MainMenuHUD::QuitButtonClicked()
    {
        onQuitButtonClicked.BroadCast();
    }
}