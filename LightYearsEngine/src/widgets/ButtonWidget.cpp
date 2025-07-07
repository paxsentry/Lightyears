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
    {
        mButtonSprite.setColor(mButtonDefaultColor);
        CenterText();
    }

    sf::FloatRect ButtonWidget::GetBound() const
    {
        return mButtonSprite.getGlobalBounds();
    }

    void ButtonWidget::SetButtonText(const std::string& text)
    {
        mButtonText.setString(text);
        CenterText();
    }

    void ButtonWidget::SetButtonTextSize(unsigned int characterSize)
    {
        mButtonText.setCharacterSize(characterSize);
        CenterText();
    }

    bool ButtonWidget::HandleEvent(const sf::Event& windowEvent)
    {
        bool handled = false;

        if (const auto* mouseEvent = windowEvent.getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouseEvent->button == sf::Mouse::Button::Left)
            {
                if (mButtonSprite.getGlobalBounds().contains({
                    (float)mouseEvent->position.x,
                    (float)mouseEvent->position.y })
                    && mIsButtonDown);
                {
                    onButtonClick.BroadCast();
                    handled = true;
                }
            }

            ButtonUp();
        }
        else if (const auto* mouseEvent = windowEvent.getIf<sf::Event::MouseButtonPressed>())
        {
            if (mButtonSprite.getGlobalBounds().contains({
                    (float)mouseEvent->position.x,
                    (float)mouseEvent->position.y })
                    )
            {
                ButtonDown();
                handled = true;
            }
        }
        else if (const auto* mouseEvent = windowEvent.getIf<sf::Event::MouseMoved>())
        {
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (mButtonSprite.getGlobalBounds().contains({
                    (float)mouseEvent->position.x,
                    (float)mouseEvent->position.y }))
                {
                    MouseHover();
                }
                else
                {
                    ButtonUp();
                }
                handled = true;
            }
        }

        return handled || Widget::HandleEvent(windowEvent);
    }

    void ButtonWidget::Draw(sf::RenderWindow& window)
    {
        window.draw(mButtonSprite);
        window.draw(mButtonText);
    }

    void ButtonWidget::LocationUpdated(const sf::Vector2f& newLocation)
    {
        mButtonSprite.setPosition(newLocation);
        CenterText();
    }

    void ButtonWidget::RotationUpdated(const sf::Angle& newRotation)
    {
        mButtonSprite.setRotation(newRotation);
        mButtonText.setRotation(newRotation);
    }

    void ButtonWidget::CenterText()
    {
        sf::Vector2f widgetCenter = GetCenterPosition();
        sf::FloatRect textBound = mButtonText.getGlobalBounds();

        mButtonText.setPosition(widgetCenter - sf::Vector2f{ textBound.size.x / 2.f, textBound.size.y });
    }
    void ButtonWidget::ButtonUp()
    {
        mIsButtonDown = false;
        mButtonSprite.setColor(mButtonDefaultColor);
    }

    void ButtonWidget::ButtonDown()
    {
        mIsButtonDown = true;
        mButtonSprite.setColor(mButtonDownColor);
    }

    void ButtonWidget::MouseHover()
    {
        mButtonSprite.setColor(mButtonHoverColor);
    }
}