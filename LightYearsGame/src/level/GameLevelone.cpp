#include "enemy/BossStage.h"
#include "enemy/ChaosStage.h"
#include "enemy/HexagonStage.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/UFOStage.h"
#include "enemy/VanguardStage.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/AssetsManager.h"
#include "framework/BackdropActor.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "level/GameLevelone.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "widget/GameplayHUD.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application* application)
        : World(application)
    {}

    void GameLevelOne::BeginPlay()
    {
        SpawnCosmetics();
        Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
        mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
        mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);

        mGameplayHUD = SpawnHUD<GameplayHUD>();
        mGameplayHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::QuitGame);
        mGameplayHUD.lock()->onRestartButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::RestartGame);
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<VanguardStage>{new VanguardStage{ this }});
        AddStage(shared<WaitStage>{new WaitStage{ this, 0.5f }});

        AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});
        AddStage(shared<WaitStage>{new WaitStage{ this, 1.f }});

        AddStage(shared<HexagonStage>{new HexagonStage{ this }});
        AddStage(shared<WaitStage>{new WaitStage{ this, 2.f }});

        AddStage(shared<UFOStage>{new UFOStage{ this }});
        AddStage(shared<WaitStage>{new WaitStage{ this, 3.f }});

        AddStage(shared<ChaosStage>{new ChaosStage{ this }});
        AddStage(shared<WaitStage>{new WaitStage{ this, 3.f }});

        AddStage(shared<BossStage>{new BossStage{ this }});
    }

    void GameLevelOne::AllGameStageFinished()
    {
        mGameplayHUD.lock()->GameFinished(true);
    }

    void GameLevelOne::PlayerSpaceshipDestroyed(Actor* playerSpaceship)
    {
        mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);

        if (!mPlayerSpaceship.expired())
        {
            mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
        }
        else
        {
            GameOver();
        }
    }

    void GameLevelOne::GameOver()
    {
        mGameplayHUD.lock()->GameFinished(false);
    }

    void GameLevelOne::RestartGame()
    {
        PlayerManager::Get().Reset();
        GetApplication()->LoadWorld<GameLevelOne>();
    }

    void GameLevelOne::SpawnCosmetics()
    {
        auto backdropActor = SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/darkPurple.png");
    }

    void GameLevelOne::QuitGame()
    {
        GetApplication()->QuitApplication();
    }
}