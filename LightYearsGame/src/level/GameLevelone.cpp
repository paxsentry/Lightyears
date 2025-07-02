#include "enemy/HexagonStage.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/UFOStage.h"
#include "enemy/VanguardStage.h"
#include "framework/Actor.h"
#include "framework/AssetsManager.h"
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
        Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
        mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
        mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);

        mGameplayHUD = SpawnHUD<GameplayHUD>();
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<WaitStage>{new WaitStage{ this, 0.5f }});
        AddStage(shared<UFOStage>{new UFOStage{ this }});

        AddStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
        AddStage(shared<HexagonStage>{new HexagonStage{ this }});

        AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
        AddStage(shared<VanguardStage>{new VanguardStage{ this }});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});
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
        LOG("GAME OVER!!!");
    }
}