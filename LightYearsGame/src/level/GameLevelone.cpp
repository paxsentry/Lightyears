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
#include "player/PlayerSpaceship.h"
#include "player/PlayerManager.h"

namespace ly
{
    GameLevelone::GameLevelone(Application* application)
        :World(application)
    {
        Player newPlayer = PlayerManager::Get().CreateNewPlayer();
        newPlayer.SpawnSpaceship(this);
    }

    void GameLevelone::BeginPlay()
    {}

    void GameLevelone::InitGameStages()
    {
        AddStage(shared<WaitStage>{new WaitStage{ this, 1.f }});
        AddStage(shared<UFOStage>{new UFOStage{ this }});

        AddStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
        AddStage(shared<HexagonStage>{new HexagonStage{ this }});

        AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
        AddStage(shared<VanguardStage>{new VanguardStage{ this }});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});
    }
}