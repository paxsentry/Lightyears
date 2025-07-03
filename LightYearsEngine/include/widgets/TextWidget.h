#pragma once
#include "framework/Core.h"
#include "widgets/Widget.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class TextWidget : public Widget
    {
    public:
        TextWidget(const std::string& text, const std::string& fontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf", unsigned int characterSize = 10);

        void SetText(const std::string& newText);
        void SetTextSize(unsigned int newSize);
        virtual sf::FloatRect GetBound() const override;

    private:
        sf::Text mText;
        shared<sf::Font> mFont;

        virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
        virtual void RotationUpdated(const sf::Angle& newRotation) override;
        virtual void Draw(sf::RenderWindow& window) override;
    };
}