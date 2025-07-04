#include "framework/AssetsManager.h"
#include "widgets/TextWidget.h"

namespace ly
{
    TextWidget::TextWidget(const std::string& text, const std::string& fontPath, unsigned int characterSize)
        :mFont{ AssetsManager::Get().LoadFont(fontPath) },
        mText{ *(mFont.get()), text, characterSize }
    {
        mText.setFont(*mFont);
    }

    void TextWidget::SetText(const std::string& newText)
    {
        mText.setString(newText);
    }

    void TextWidget::SetTextSize(unsigned int newSize)
    {
        mText.setCharacterSize(newSize);
    }

    sf::FloatRect TextWidget::GetBound() const
    {
        return mText.getGlobalBounds();
    }

    void TextWidget::LocationUpdated(const sf::Vector2f& newLocation)
    {
        mText.setPosition(newLocation);
    }

    void TextWidget::RotationUpdated(const sf::Angle& newRotation)
    {
        mText.setRotation(newRotation);
    }

    void TextWidget::Draw(sf::RenderWindow& window)
    {
        // TODO check why is this needed
        mText.setFont(*mFont);
        window.draw(mText);
    }
}