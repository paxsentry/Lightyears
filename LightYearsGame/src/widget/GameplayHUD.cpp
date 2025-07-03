#include "framework/Actor.h"
#include "player/Player.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "widget/GameplayHUD.h"

namespace ly
{
    GameplayHUD::GameplayHUD()
        :mFpsText{ "FPS:" },
        mPlayerHealthBar{},
        mHealthyHealthBarColor{ 128,255,128,255 },
        mCriticalHealthBarColor{ 255,128,128,255 },
        mCriticalThreshold{ 0.3f },
        mPlayerLifeIcon{ "SpaceShooterRedux/PNG/UI/playerLife1_blue.png" },
        mWidgetSpacing {10.f}
    {
        mFpsText.SetTextSize(27);
    }

    void GameplayHUD::Draw(sf::RenderWindow& window)
    {
        mFpsText.NativeDraw(window);
        mPlayerHealthBar.NativeDraw(window);
        mPlayerLifeIcon.NativeDraw(window);
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

        sf::Vector2f lifeIconPos = mPlayerHealthBar.GetWidgetLocation();
        lifeIconPos += sf::Vector2f{ mPlayerHealthBar.GetBound().size.x + mWidgetSpacing, 0.f };

        mPlayerLifeIcon.SetWidgetLocation(lifeIconPos);

        RefreshHealthBar();
    }

    void GameplayHUD::PlayerHealthUpdated(float amount, float currentHealth, float maxHealth)
    {
        mPlayerHealthBar.UpdateValue(currentHealth, maxHealth);
        if (currentHealth / maxHealth < mCriticalThreshold)
        {
            mPlayerHealthBar.SetForegroundColor(mCriticalHealthBarColor);
        }
        else
        {
            mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
        }
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