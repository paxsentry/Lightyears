#include "widgets/Widget.h"

namespace ly
{
    Widget::Widget()
        :mIsVisible{ true },
        mWidgetTransform{}
    {}

    void Widget::Draw(sf::RenderWindow & window)
    {}

    void Widget::LocationUpdated(const sf::Vector2f & newLocation)
    {}

    void Widget::RotationUpdated(const sf::Angle & newRotation)
    {}

    void Widget::NativeDraw(sf::RenderWindow& window)
    {
        if (mIsVisible)
        {
            Draw(window);
        }
    }

    bool Widget::HandleEvent(const sf::Event& event)
    {
        return false;
    }

    void Widget::SetWidgetLocation(const sf::Vector2f& newLocation)
    {
        mWidgetTransform.setPosition(newLocation);
        LocationUpdated(newLocation);
    }

    void Widget::SetWidgetRotation(const sf::Angle& newRotation)
    {
        mWidgetTransform.setRotation(newRotation);
        RotationUpdated(newRotation);
    }

    void Widget::SetVisibility(bool newVisibility)
    {
        mIsVisible = newVisibility;
    }

    sf::Vector2f Widget::GetCenterPosition() const
    {
        sf::FloatRect bound = GetBound();
        auto csd= sf::Vector2f{bound.position.x + bound.size.x/2.f, bound.position.y + bound.size.y/2.f};

        auto wer = bound.getCenter();

        return csd;
    }
}