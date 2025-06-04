#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

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

    void PhysicsSystem::Step(float deltaTime)
    {
        b2World_Step(mPhysicsWorld, deltaTime, mSubStepCount);
    }

    b2BodyId* PhysicsSystem::AddListener(Actor* listener)
    {
        if (listener->IsPendingDestruction()) return nullptr;

        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.userData = reinterpret_cast<void*>(listener);
        bodyDef.position.x = listener->GetActorLocation().x * GetPhysicsScale();
        bodyDef.position.y = listener->GetActorLocation().y * GetPhysicsScale();
        bodyDef.rotation = b2MakeRot(listener->GetActorRotation().asRadians());

        b2BodyId body = b2CreateBody(mPhysicsWorld, &bodyDef);

        auto listenerBounds = listener->GetActorGlobalBounds();
        b2Polygon box = b2MakeBox(
            listenerBounds.size.x / 2 * GetPhysicsScale(),
            listenerBounds.size.y / 2 * GetPhysicsScale()
        );
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.density = 1.0f;
        shapeDef.material.friction = 0.3f;
        shapeDef.isSensor = true;

        b2ShapeId shapeId = b2CreatePolygonShape(body, &shapeDef, &box);

        return &body;
    }

    PhysicsSystem::PhysicsSystem()
        : mPhysicsScale{ 0.01f },
        mSubStepCount{ 4 }
    {
        mWorldDef.gravity = mGravity;
        mPhysicsWorld = b2CreateWorld(&mWorldDef);
    }
}