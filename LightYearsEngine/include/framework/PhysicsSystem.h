#pragma once
#include "framework/Core.h"
#include <box2d/box2d.h>

namespace ly
{
    class Actor;

    

    class PhysicsSystem
    {
    public:
        static PhysicsSystem& Get();
        void Step(float deltaTime);
        b2BodyId AddListener(Actor* listener) const;
        void RemoverListener(b2BodyId bodyToRemove);
        float GetPhysicsScale() const { return mPhysicsScale; }
        void CheckContact();

    protected:
        PhysicsSystem();

    private:
        static unique<PhysicsSystem> physicsSystem;
        b2Vec2 mGravity = { 0.0f, 0.0f };

        b2WorldDef mWorldDef = b2DefaultWorldDef();
        b2WorldId mPhysicsWorld;
        float mPhysicsScale; // to reduce Box2d meter based system, cm feels faster.
        int mSubStepCount;

        void BeginContact(b2SensorBeginTouchEvent* contact);
        void EndContact(b2SensorEndTouchEvent* contact);
    };
}