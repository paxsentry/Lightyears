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
            float damage = 10.f);

        void SetSpeed(float newSpeed);
        void SetDamage(float newDamage);

        virtual void Tick(float deltaTime) override;

    private:
        void Move(float deltaTime);

        Actor* mOwner;
        float mSpeed;
        float mDamage;
    };
}