#include "level/MainMenu.h"
#include "widget/MainMenuHUD.h"

namespace ly
{
    MainMenu::MainMenu(Application* owner)
        : World{ owner }
    {
        mMainMenuHUD = SpawnHUD<MainMenuHUD>();
    }

    void MainMenu::BeginPlay()
    {
        mMainMenuHUD.lock()->onStartButtonClicked.BindAction(GetWeakRef(), &MainMenu::StartGame);
        mMainMenuHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &MainMenu::QuitGame);
    }

    void MainMenu::StartGame()
    {
        LOG("Start game");
    }

    void MainMenu::QuitGame()
    {
        LOG("Quit game");
    }
}