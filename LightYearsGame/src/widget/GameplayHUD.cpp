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
        mPlayerLifeIcon{ "SpaceShooterRedux/PNG/UI/playerLife1_blue.png" },
        mPlayerLifeText{ "" },
        mPlayerScoreIcon{ "SpaceShooterRedux/PNG/Power-ups/star_gold.png" },
        mPlayerScoreText{ "" },
        mHealthyHealthBarColor{ 128,255,128,255 },
        mCriticalHealthBarColor{ 255,128,128,255 },
        mCriticalThreshold{ 0.3f },
        mWidgetSpacing{ 10.f },
        mTestButton{}
    {
        mFpsText.SetTextSize(27);
        mPlayerLifeText.SetTextSize(27);
        mPlayerScoreText.SetTextSize(27);
    }

    void GameplayHUD::Draw(sf::RenderWindow& window)
    {
        mFpsText.NativeDraw(window);
        mPlayerHealthBar.NativeDraw(window);
        mPlayerLifeIcon.NativeDraw(window);
        mPlayerLifeText.NativeDraw(window);
        mPlayerScoreIcon.NativeDraw(window);
        mPlayerScoreText.NativeDraw(window);
        mTestButton.NativeDraw(window);
    }

    void GameplayHUD::Tick(float deltaTime)
    {
        int fps = int(1 / deltaTime);
        std::string fpsText = "FPS: " + std::to_string(fps);
        mFpsText.SetText(fpsText);
    }

    bool GameplayHUD::HandleEvent(const sf::Event& event)
    {
       return mTestButton.HandleEvent(event) || HUD::HandleEvent(event);
    }

    void GameplayHUD::Init(const sf::RenderWindow& window)
    {
        auto windowSize = window.getSize();
        mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{ 20.f, windowSize.y - 50.f });

        sf::Vector2f nextWidgetPos = mPlayerHealthBar.GetWidgetLocation();
        nextWidgetPos += sf::Vector2f{ mPlayerHealthBar.GetBound().size.x + mWidgetSpacing, 0.f };
        mPlayerLifeIcon.SetWidgetLocation(nextWidgetPos);

        nextWidgetPos += sf::Vector2f{ mPlayerLifeIcon.GetBound().size.x + mWidgetSpacing, 0.f };
        mPlayerLifeText.SetWidgetLocation(nextWidgetPos);

        nextWidgetPos += sf::Vector2f{ mPlayerLifeText.GetBound().size.x + mWidgetSpacing * 4.f, 0.f };
        mPlayerScoreIcon.SetWidgetLocation(nextWidgetPos);

        nextWidgetPos += sf::Vector2f{ mPlayerScoreIcon.GetBound().size.x + mWidgetSpacing, 0.f };
        mPlayerScoreText.SetWidgetLocation(nextWidgetPos);

        mTestButton.SetWidgetLocation({ windowSize.x / 2.f, windowSize.y / 2.f });
        mTestButton.SetButtonTextSize(20);
        mTestButton.onButtonClick.BindAction(GetWeakRef(), &GameplayHUD::TestButtonclicked);

        RefreshHealthBar();
        ConnectPlayerStats();
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
            PlayerHealthUpdated(0.f, healthComp.GetHealth(), healthComp.GetMaxHealth());
        }
    }

    void GameplayHUD::ConnectPlayerStats()
    {
        Player* player = PlayerManager::Get().GetPlayer();
        if (player)
        {
            int lifeCount = player->GetLifeCount();
            mPlayerLifeText.SetText(std::to_string(lifeCount));
            player->onLifeChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerLifeCountUpdated);

            int playerScore = player->GetScore();
            mPlayerScoreText.SetText(std::to_string(playerScore));
            player->onScoreChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerScoreUpdated);
        }
    }

    void GameplayHUD::PlayerLifeCountUpdated(int amount)
    {
        mPlayerLifeText.SetText(std::to_string(amount));
    }

    void GameplayHUD::PlayerScoreUpdated(int amount)
    {
        mPlayerScoreText.SetText(std::to_string(amount));
    }

    void GameplayHUD::PlayerSpaceshipDestroyed(Actor* actor)
    {
        RefreshHealthBar();
    }
    void GameplayHUD::TestButtonclicked()
    {
        LOG("Button works!");
    }
}