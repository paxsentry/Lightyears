#include "config.h"
#include "framework/AssetsManager.h"
#include "gameFramework/GameApplication.h"
#include "level/GameLevelone.h"
#include "level/MainMenu.h"

ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
        :Application{ 1024, 1440,"Light years", sf::Style::Titlebar | sf::Style::Close }
    {
        AssetsManager::Get().SetAssetsRootDirectory(GetResourceDir());

        weak<MainMenu> newWorld = LoadWorld<MainMenu>();
    }
}
