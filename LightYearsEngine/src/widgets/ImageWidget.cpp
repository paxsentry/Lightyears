#include "framework/AssetsManager.h"
#include "widgets/ImageWidget.h"

namespace ly
{
    ImageWidget::ImageWidget(const std::string& imagePath)
        : mTexture{ AssetsManager::Get().LoadTexture(imagePath) },
        mSprite{ *(mTexture.get()) }
    {}

    void ImageWidget::SetImage(const shared<sf::Texture>&newTexture)
    {
        if (newTexture)
        {
            mTexture = newTexture;
            mSprite.setTexture(*(mTexture.get()));
        }
    }

    sf::FloatRect ImageWidget::GetBound() const
    {
        return mSprite.getGlobalBounds();
    }

    void ImageWidget::Draw(sf::RenderWindow& window)
    {
        window.draw(mSprite);
    }

    void ImageWidget::LocationUpdated(const sf::Vector2f& newLocation)
    {
        mSprite.setPosition(newLocation);
    }

    void ImageWidget::RotationUpdated(const sf::Angle& newRotation)
    {
        mSprite.setRotation(newRotation);
    }
}