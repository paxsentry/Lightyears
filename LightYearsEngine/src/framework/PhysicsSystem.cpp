#include "framework/PhysicsSystem.h"

namespace ly
{
    unique<PhysicsSystem> PhysicsSystem::physicsSystem{ nullptr };

    PhysicsSystem& PhysicsSystem::Get()
    {
        if (!physicsSystem)
        {
            physicsSystem = std::move(unique<PhysicsSystem> {new PhysicsSystem});
        }

        return *physicsSystem;
    }

    PhysicsSystem::PhysicsSystem()
        : mPhysicsScale{ 0.01f }
    {
        mWorldDef.gravity = mGravity;
        mPhysicsWorld = b2CreateWorld(&mWorldDef);
    }
}