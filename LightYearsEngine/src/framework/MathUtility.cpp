#include "framework/MathUtility.h"

namespace ly
{
    const float PI = 3.1415926535;

    sf::Vector2f RotationToVector(float rotation)
    {
        float radians = DegreesToRadians(rotation);
        return sf::Vector2f(std::cos(radians), std::sin(radians));
    }

    float DegreesToRadians(float degrees)
    {
        return degrees * (PI / 180.0f);
    }

    float RadiansToDegrees(float radians)
    {
        return radians * (180.f / PI);
    }

    float LerpFloat(float a, float b, float alpha)
    {
        if (alpha > 1.f) alpha = 1.f;
        if (alpha < 0.f) alpha = 0.f;

        return a + (b - a) * alpha;
    }

    sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha)
    {
        int lerpR = LerpFloat(a.r, b.r, alpha);
        int lerpG = LerpFloat(a.g, b.g, alpha);
        int lerpB = LerpFloat(a.b, b.b, alpha);
        int lerpA = LerpFloat(a.a, b.a, alpha);

        return sf::Color(lerpR, lerpG, lerpB, lerpA);
    }

    sf::Vector2f LerpVector2f(const sf::Vector2f& a, const sf::Vector2f& b, float alpha)
    {
        float lerpX = LerpFloat(a.x, b.x, alpha);
        float lerpY = LerpFloat(a.y, b.y, alpha);
        
        return sf::Vector2f(lerpX, lerpY);
    }
}