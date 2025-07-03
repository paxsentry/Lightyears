#pragma once
#include "widgets/Widget.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class ImageWidget : public Widget
    {
    public:
        ImageWidget(const std::string& imagePath);
        void SetImage(const shared<sf::Texture>& newTexture);

    private:
        shared<sf::Texture> mTexture;
        sf::Sprite mSprite;

        virtual void Draw(sf::RenderWindow& window) override;
        virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
        virtual void RotationUpdated(const sf::Angle& newRotation) override;
    };
}