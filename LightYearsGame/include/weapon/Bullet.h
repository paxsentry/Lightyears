#pragma once
#include "framework/Actor.h"

namespace ly
{
    class Bullet : public Actor
    {
    public:
        Bullet(World* owningWorld, Actor* owner,
            const std::string& texturePath,
            float speed = 900.f,
            float damage = 5.f);

        void SetSpeed(float newSpeed);
        void SetDamage(float newDamage);
        float GetDamage() const { return mDamage; }

        virtual void Tick(float deltaTime) override;
        virtual void BeginPlay() override;

    private:
        void Move(float deltaTime);
        virtual void OnActorBeginOverlap(Actor* other) override;

        Actor* mOwner;
        float mSpeed;
        float mDamage;
    };
}