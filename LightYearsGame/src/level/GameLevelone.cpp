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
#include "framework/BackgroundLayer.h"
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
        weak<BackgroundLayer> planets = SpawnActor<BackgroundLayer>();
        planets.lock()->SetAssets({
            "SpaceShooterRedux/PNG/Planets/Planet1.png",
            "SpaceShooterRedux/PNG/Planets/Planet2.png",
            "SpaceShooterRedux/PNG/Planets/Planet3.png",
            "SpaceShooterRedux/PNG/Planets/Planet4.png",
            "SpaceShooterRedux/PNG/Planets/Planet5.png",
            "SpaceShooterRedux/PNG/Planets/Planet6.png",
            "SpaceShooterRedux/PNG/Planets/Planet7.png"
            });

        planets.lock()->SetSpriteCount(3);
        planets.lock()->SetSizes(.1f, .5f);
        planets.lock()->SetVelocities({ 0.f,30.f }, { 0.f,80.f });

        weak<BackgroundLayer> meteors = SpawnActor<BackgroundLayer>();
        meteors.lock()->SetAssets({
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_big1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_big2.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_big3.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_med1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_med3.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_small1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_small2.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny2.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_big1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_big2.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_big3.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_med1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_small1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_small2.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny1.png",
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny2.png",
            });

        meteors.lock()->SetSpriteCount(22);
        meteors.lock()->SetSizes(.2f, .4f);
    }

    void GameLevelOne::QuitGame()
    {
        GetApplication()->QuitApplication();
    }
}