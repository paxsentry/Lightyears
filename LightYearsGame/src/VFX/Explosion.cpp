#include "framework/MathUtility.h"
#include "framework/World.h"
#include "VFX/Explosion.h"
#include "VFX/Particle.h"

namespace ly
{
    Explosion::Explosion(int particleAmount, float lifeMin, float lifeMax, float sizeMin, float sizeMax, float speedMin, float speedMax, const sf::Color& particleColor, const List<std::string>& particleImagePaths)
        : mParticleAmount{ particleAmount },
        mLifeTimeMin{ lifeMin },
        mLifeTimeMax{ lifeMax },
        mSizeMin{ sizeMin },
        mSizeMax{ sizeMax },
        mSpeedMin{ speedMin },
        mSpeedMax{ speedMax },
        mParticleColor{ particleColor },
        mParticleImagePaths{ particleImagePaths }
    {}

    void Explosion::SpawnExplosion(World* world, const sf::Vector2f& location)
    {
        if (!world) { return; }

        for (int i = 0; i < mParticleAmount; i++)
        {
            std::string particleImagePath = mParticleImagePaths[(int)RandomRange(0, mParticleImagePaths.size())];
            weak<Particle> newParticle = world->SpawnActor<Particle>(particleImagePath);

            newParticle.lock()->SetActorLocation(location);
            newParticle.lock()->RandomLifetime(mLifeTimeMin, mLifeTimeMax);
            newParticle.lock()->RandomSize(mSizeMin, mSizeMax);
            newParticle.lock()->RandomVelocity(mSpeedMin, mSpeedMax);
            newParticle.lock()->GetSprite().setColor(mParticleColor);
        }
    }
}