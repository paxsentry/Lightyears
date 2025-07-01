#include "framework/AssetsManager.h"
#include "widgets/ValueGauge.h"

namespace ly
{
    ValueGauge::ValueGauge(const sf::Vector2f& size, float initialPercent, const sf::Color& foregroundColor, const sf::Color& backgroundColor)
        : Widget{},
        mTextFont{ AssetsManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf") },
        mText{ *(mTextFont.get()),"" },
        mPercent{ initialPercent },
        mBarFront{ size },
        mBarBack{ size },
        mForegroundColor{ foregroundColor },
        mBackgroundColor{ backgroundColor }
    {
        mBarFront.setFillColor(mForegroundColor);
        mBarBack.setFillColor(mBackgroundColor);
    }

    void ValueGauge::UpdateValue(float value, float maxValue)
    {
        if (maxValue == 0) return;

        mPercent = value / maxValue;

        std::string displayStr = std::to_string((int)value) + "/" + std::to_string((int)maxValue);

        mText.setString(displayStr);

        sf::Vector2f barsize = mBarBack.getSize();
        mBarFront.setSize({ barsize.x * mPercent, barsize.y });
    }

    void ValueGauge::Draw(sf::RenderWindow& window)
    {
        mText.setFont(*mTextFont);
        window.draw(mBarBack);
        window.draw(mBarFront);
        window.draw(mText);
    }

    void ValueGauge::LocationUpdated(const sf::Vector2f& newLocation)
    {
        mText.setPosition(newLocation);
        mBarFront.setPosition(newLocation);
        mBarBack.setPosition(newLocation);
    }

    void ValueGauge::RotationUpdated(const sf::Angle& newRotation)
    {
        mText.setRotation(newRotation);
        mBarFront.setRotation(newRotation);
        mBarBack.setRotation(newRotation);
    }
}