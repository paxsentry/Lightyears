#pragma
#include "framework/Core.h"
#include <string>

namespace ly
{
    class World;

    class Explosion
    {
    public:
        Explosion(int particleAmount = 20,
            float lifeMin = .05f,
            float lifeMax = 1.5f,
            float sizeMin = 1.5f,
            float sizeMax = 3.5f,
            float speedMin = 200.f,
            float speedMax = 400.f,
            const sf::Color& particleColor = sf::Color(255, 128, 0, 255),
            const List<std::string>& particleImagePaths = {
                "SpaceShooterRedux/PNG/Effects/star1.png",
                "SpaceShooterRedux/PNG/Effects/star2.png",
                "SpaceShooterRedux/PNG/Effects/star3.png"
            });

        void SpawnExplosion(World* world, const sf::Vector2f& location);

    private:
        int mParticleAmount;
        float mLifeTimeMin;
        float mLifeTimeMax;
        float mSizeMin;
        float mSizeMax;
        float mSpeedMin;
        float mSpeedMax;
        sf::Color mParticleColor;

        List<std::string> mParticleImagePaths;
    };
}