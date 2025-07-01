#include "widget/GameplayHUD.h"

namespace ly
{
    GameplayHUD::GameplayHUD()
        :mFpsText{ "FPS:" },
        mPlayerHealthBar{}
    {
        mFpsText.SetTextSize(27);
    }

    void GameplayHUD::Draw(sf::RenderWindow& window)
    {
        mFpsText.NativeDraw(window);
        mPlayerHealthBar.NativeDraw(window);
    }

    void GameplayHUD::Tick(float deltaTime)
    {
        int fps = int(1 / deltaTime);
        std::string fpsText = "FPS: " + std::to_string(fps);
        mFpsText.SetText(fpsText);
    }

    void GameplayHUD::Init(const sf::RenderWindow& window)
    {
        auto windowSize = window.getSize();
        mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{ 20.f, windowSize.y - 50.f });
        mPlayerHealthBar.UpdateValue(100.f, 150.f);
    }
}