#pragma once
#include "widgets/Widget.h"

namespace ly
{
    class ValueGauge : public Widget
    {
    public:
        ValueGauge(const sf::Vector2f& size = sf::Vector2f{ 300.f, 40.f },
            float initialPercent = 0.75f,
            const sf::Color& foregroundColor = sf::Color{ 128,255,128,255 },
            const sf::Color& backgroundColor = sf::Color{ 128,128,128,255 });
        void UpdateValue(float value, float maxValue);

    private:
        virtual void Draw(sf::RenderWindow& window) override;
        virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
        virtual void RotationUpdated(const sf::Angle& newRotation) override;

        sf::Text mText;
        shared<sf::Font> mTextFont;

        sf::RectangleShape mBarFront;
        sf::RectangleShape mBarBack;
        sf::Color mForegroundColor;
        sf::Color mBackgroundColor;

        float mPercent;
    };
}