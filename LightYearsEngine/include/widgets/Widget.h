#pragma once
#include "framework/Object.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class Widget : public Object
    {
    public:
        void NativeDraw(sf::RenderWindow& window);
        virtual bool HandleEvent(const sf::Event& event);
        void SetWidgetLocation(const sf::Vector2f& newLocation);
        void SetWidgetRotation(const sf::Angle& newRotation);
        sf::Vector2f GetWidgetLocation() const { return mWidgetTransform.getPosition(); }
        sf::Angle GetWidgetRotation() const { return mWidgetTransform.getRotation(); }
        void SetVisibility(bool newVisibility);
        bool GetVisibility() const { return mIsVisible; }

    protected:
        Widget();

    private:
        sf::Transformable mWidgetTransform;
        bool mIsVisible;

        virtual void Draw(sf::RenderWindow& window);
        virtual void LocationUpdated(const sf::Vector2f& newLocation);
        virtual void RotationUpdated(const sf::Angle& newRotation);
    };
}