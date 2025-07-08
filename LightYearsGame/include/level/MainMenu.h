#pragma once
#include "framework/World.h"

namespace ly
{
    class MainMenuHUD;

    class MainMenu : public World
    {
    public:
        MainMenu(Application* owner);

        virtual void BeginPlay() override;

    private:
        weak<MainMenuHUD> mMainMenuHUD;
        void StartGame();
        void QuitGame();
    };
}