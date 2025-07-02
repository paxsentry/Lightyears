#include "widget/GameplayHUD.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "player/Player.h"
#include "framework/Actor.h"

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

        RefreshHealthBar();
    }

    void GameplayHUD::PlayerHealthUpdated(float amount, float currentHealth, float maxHealth)
    {
        mPlayerHealthBar.UpdateValue(currentHealth, maxHealth);
    }

    void GameplayHUD::RefreshHealthBar()
    {
        Player* player = PlayerManager::Get().GetPlayer();

        if (player && !player->GetCurrentSpaceship().expired())
        {
            weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
            playerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestroyed);

            HealthComponent& healthComp = player->GetCurrentSpaceship().lock()->GetHealthComponent();

            healthComp.onHealthChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);

            mPlayerHealthBar.UpdateValue(healthComp.GetHealth(), healthComp.GetMaxHealth());
        }
    }

    void GameplayHUD::PlayerSpaceshipDestroyed(Actor* actor)
    {
        RefreshHealthBar();
    }
}