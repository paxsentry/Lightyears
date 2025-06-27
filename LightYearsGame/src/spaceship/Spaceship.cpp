#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"
#include "VFX/Explosion.h"

namespace ly
{
    Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
        :Actor{ owningWorld, texturePath },
        mVelocity{},
        mHealthComp{ 100.f, 100.f },
        mBlinkTime{ 0.f },
        mBlinkDuration{ 0.2f },
        mBlinkColorOffset{ 255,0,0,255 }
    {}

    void Spaceship::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        AddActorLocationOffset(GetVelocity() * deltaTime);
        UpdateBlink(deltaTime);
    }

    void Spaceship::SetVelocity(const sf::Vector2f& newVelocity)
    {
        mVelocity = newVelocity;
    }

    void Spaceship::Shoot()
    {}

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
        mHealthComp.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
        mHealthComp.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
        mHealthComp.onHealthEmtpy.BindAction(GetWeakRef(), &Spaceship::Blow);
    }

    void Spaceship::ApplyDamage(float amount)
    {
        mHealthComp.ChangeHealth(-amount);
    }

    void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
    {
        LOG("Health is changed by %f, now it is %f/%f", amount, health, maxHealth);
    }

    void Spaceship::OnTakenDamage(float amount, float health, float maxHealth)
    {
        Blink();
    }

    void Spaceship::Blow()
    {
        Explosion* exp = new Explosion();
        exp->SpawnExplosion(GetWorld(), GetActorLocation());
        Blew();
        Destroy();
        delete exp;
    }

    void Spaceship::Blew()
    {}

    void Spaceship::Blink()
    {
        if (mBlinkTime == 0)
        {
            mBlinkTime = mBlinkDuration;
        }
    }

    void Spaceship::UpdateBlink(float deltaTime)
    {
        if (mBlinkTime > 0)
        {
            mBlinkTime -= deltaTime;
            mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f;

            GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
        }
    }
}