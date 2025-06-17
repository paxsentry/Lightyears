#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
    sf::Vector2f RotationToVector(float rotation);
    float DegreesToRadians(float degrees);
    float RadiansToDegrees(float radians);

    template<typename T>
    float  GetVectorLength(const sf::Vector2<T>& vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    template<typename T>
    sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vector, float amount)
    {
        vector.x *= amount;
        vector.y *= amount;

        return vector;
    }

    template<typename T>
    sf::Vector2<T>& Normalise(sf::Vector2<T>& vector)
    {
        float vectLen = GetVectorLength<T>(vector);

        if (vectLen == 0.f) { return sf::Vector2<T>{}; }

        ScaleVector(vector, 1.0 / vectLen);

        return vector;
    }

    float LerpFloat(float a, float b, float alpha);

    sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha);

    sf::Vector2f LerpVector2f(const sf::Vector2f& a, const sf::Vector2f& b, float alpha);

    float RandomRange(float min, float max);

    sf::Vector2f RandomUnitVector();
}