#include "enemy/HexagonStage.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/UFO.h"
#include "enemy/Vanguard.h"
#include "enemy/VanguardStage.h"
#include "framework/Actor.h"
#include "framework/AssetsManager.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "level/GameLevelone.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    GameLevelone::GameLevelone(Application* application)
        :World(application)
    {
        testPlayer = SpawnActor<PlayerSpaceship>();
        testPlayer.lock()->SetActorLocation(sf::Vector2f(512.f, 770.f));
        testPlayer.lock()->SetActorRotation(0.f);
    }

    void GameLevelone::BeginPlay()
    {
        weak<UFO> newUfo = SpawnActor<UFO>(sf::Vector2f{ 0.f,0.f });
        newUfo.lock()->SetActorLocation({ GetWindowSize().x / 2.f, GetWindowSize().y / 2.f -200.f});
    }

    void GameLevelone::InitGameStages()
    {
        AddStage(shared<HexagonStage>{new HexagonStage{ this }});
        AddStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
        AddStage(shared<VanguardStage>{new VanguardStage{ this }});
        AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});
    }
}