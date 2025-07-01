#include "widget/GameplayHUD.h"

namespace ly
{
    GameplayHUD::GameplayHUD()
        :mFpsText{"FPS:"}
    {
        mFpsText.SetTextSize(27);
    }

    void GameplayHUD::Draw(sf::RenderWindow& window)
    {
        mFpsText.NativeDraw(window);
    }

    void GameplayHUD::Tick(float deltaTime)
    {
        int fps = int(1 / deltaTime);
        std::string fpsText = "FPS: " + std::to_string(fps);
        mFpsText.SetText(fpsText);
    }
}