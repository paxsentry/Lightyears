#include "framework/AssetsManager.h"
#include "widgets/ButtonWidget.h"

namespace ly
{
    ButtonWidget::ButtonWidget(const std::string& text, const std::string& texturePath)
        : mButtonTexture{ AssetsManager::Get().LoadTexture(texturePath) },
        mButtonSprite{ *(mButtonTexture.get()) },
        mButtonFont{ AssetsManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf") },
        mButtonText{ *(mButtonFont.get()), text },
        mButtonDefaultColor{ 128,128,128,255 },
        mButtonDownColor{ 64,64,64,255 },
        mButtonHoverColor{ 192,192,192,255 },
        mIsButtonDown{ false }
    {}

    sf::FloatRect ButtonWidget::GetBound() const
    {
        return mButtonSprite.getGlobalBounds();
    }

    void ButtonWidget::Draw(sf::RenderWindow& window)
    {
        window.draw(mButtonSprite);
        window.draw(mButtonText);
    }

    void ButtonWidget::LocationUpdated(const sf::Vector2f& newLocation)
    {
        mButtonSprite.setPosition(newLocation);
        mButtonText.setPosition(newLocation);
    }

    void ButtonWidget::RotationUpdated(const sf::Angle& newRotation)
    {
        mButtonSprite.setRotation(newRotation);
        mButtonText.setRotation(newRotation);
    }
}