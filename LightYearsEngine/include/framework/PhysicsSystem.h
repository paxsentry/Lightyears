#pragma once
#include "framework/Core.h"
#include <box2d/box2d.h>

namespace ly
{
    class PhysicsSystem
    {
    public:
        static PhysicsSystem& Get();

    protected:
        PhysicsSystem();

    private:
        static unique<PhysicsSystem> physicsSystem;
        b2Vec2 mGravity = { 0.0f, 0.0f };

        b2WorldDef mWorldDef = b2DefaultWorldDef();
        b2WorldId mPhysicsWorld;
        float mPhysicsScale; // to reduce Box2d meter based system, cm feels faster.
    };
}