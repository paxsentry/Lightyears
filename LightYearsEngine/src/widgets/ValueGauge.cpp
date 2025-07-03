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
        mText.setFont(*mTextFont);
        SetTextSize(20);
    }

    void ValueGauge::UpdateValue(float value, float maxValue)
    {
        if (maxValue == 0) return;

        mPercent = value / maxValue;

        std::string displayStr = std::to_string((int)value) + "/" + std::to_string((int)maxValue);

        mText.setString(displayStr);

        sf::Vector2f barsize = mBarBack.getSize();
        mBarFront.setSize({ barsize.x * mPercent, barsize.y });
        CenterText();
    }

    sf::FloatRect ValueGauge::GetBound() const
    {
        return mBarBack.getGlobalBounds();
    }

    void ValueGauge::SetTextSize(unsigned int textSize)
    {
        mText.setCharacterSize(textSize);
    }

    void ValueGauge::SetForegroundColor(const sf::Color color)
    {
        mBarFront.setFillColor(color);
    }

    void ValueGauge::SetBackgroundColor(const sf::Color color)
    {
        mBarBack.setFillColor(color);
    }

    void ValueGauge::Draw(sf::RenderWindow& window)
    {
       // mText.setFont(*mTextFont);
        window.draw(mBarBack);
        window.draw(mBarFront);
        window.draw(mText);
    }

    void ValueGauge::LocationUpdated(const sf::Vector2f& newLocation)
    {
        mBarFront.setPosition(newLocation);
        mBarBack.setPosition(newLocation);
        CenterText();
    }

    void ValueGauge::RotationUpdated(const sf::Angle& newRotation)
    {
        mText.setRotation(newRotation);
        mBarFront.setRotation(newRotation);
        mBarBack.setRotation(newRotation);
    }

    void ValueGauge::CenterText()
    {
        sf::Vector2f widgetCenter = GetCenterPosition();
        sf::FloatRect textBound = mText.getGlobalBounds();

        mText.setPosition(widgetCenter - sf::Vector2f{ textBound.size.x / 2.f, textBound.size.y});
    }
}