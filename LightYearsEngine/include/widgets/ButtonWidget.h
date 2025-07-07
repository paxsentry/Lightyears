#pragma once
#include "framework/Delegate.h"
#include "widgets/Widget.h"

namespace ly
{
    class ButtonWidget : public Widget
    {
    public:
        ButtonWidget(const std::string& text = "Button",
            const std::string& texturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");

        virtual sf::FloatRect GetBound() const override;
        void SetButtonText(const std::string& text);
        void SetButtonTextSize(unsigned int characterSize);

        virtual bool HandleEvent(const sf::Event& windowEvent) override;
        Delegate<> onButtonClick;

    private:
        shared<sf::Texture> mButtonTexture;
        sf::Sprite mButtonSprite;
        shared<sf::Font> mButtonFont;
        sf::Text mButtonText;

        sf::Color mButtonDefaultColor;
        sf::Color mButtonDownColor;
        sf::Color mButtonHoverColor;

        bool mIsButtonDown;

        virtual void Draw(sf::RenderWindow& window) override;
        virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
        virtual void RotationUpdated(const sf::Angle& newRotation) override;
        void CenterText();
        void ButtonUp();
        void ButtonDown();
        void MouseHover();
    };
}