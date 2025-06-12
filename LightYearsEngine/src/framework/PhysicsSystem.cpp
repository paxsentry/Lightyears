#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

namespace ly
{
    unique<PhysicsSystem> PhysicsSystem::mPhysicsSystem{ nullptr };

    PhysicsSystem::PhysicsSystem()
        : mPhysicsScale{ 0.01f },
        mSubStepCount{ 4 }
    {
        mWorldDef.gravity = mGravity;
        mWorldDef.enableSleep = false;
        mPhysicsWorld = b2CreateWorld(&mWorldDef);
    }

    void PhysicsSystem::ProcessPendingRemove()
    {
        for (auto& elem : mPendingRemove) {
            b2DestroyBody(elem);
        }

        mPendingRemove.clear();
    }

    PhysicsSystem& PhysicsSystem::Get()
    {
        if (!mPhysicsSystem)
        {
            mPhysicsSystem = std::move(unique<PhysicsSystem> {new PhysicsSystem});
        }

        return *mPhysicsSystem;
    }

    void PhysicsSystem::Step(float deltaTime)
    {
        ProcessPendingRemove();
        b2World_Step(mPhysicsWorld, deltaTime, mSubStepCount);
        CheckContact();
    }

    b2BodyId PhysicsSystem::AddListener(Actor* listener) const
    {
        if (listener->IsPendingDestruction()) return b2BodyId { };

        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.x = listener->GetActorLocation().x * GetPhysicsScale();
        bodyDef.position.y = listener->GetActorLocation().y * GetPhysicsScale();
        bodyDef.rotation = b2MakeRot(listener->GetActorRotation().asRadians());

        b2BodyId body = b2CreateBody(mPhysicsWorld, &bodyDef);

        auto listenerBounds = listener->GetActorGlobalBounds();
        b2Polygon box = b2MakeBox(
            listenerBounds.size.x / 2 * GetPhysicsScale(),
            listenerBounds.size.y / 2  * GetPhysicsScale()
        );
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.density = 1.0f;
        shapeDef.material.friction = 0.3f;
        shapeDef.userData = reinterpret_cast<void*>(listener);
        shapeDef.isSensor = true;
        shapeDef.enableSensorEvents = true;

        b2ShapeId shapeId = b2CreatePolygonShape(body, &shapeDef, &box);

        return body;
    }

    void PhysicsSystem::RemoverListener(b2BodyId bodyToRemove)
    {
        mPendingRemove.insert(bodyToRemove);
    }

    void PhysicsSystem::CheckContact()
    {
       b2SensorEvents sensorEvent = b2World_GetSensorEvents(mPhysicsWorld);

        for (int i = 0; i < sensorEvent.beginCount; ++i) {
            BeginContact(sensorEvent.beginEvents);
        }

        for (int i = 0; i < sensorEvent.endCount; ++i) {
            EndContact(sensorEvent.endEvents);
        }
    }

    void PhysicsSystem::Cleanup()
    {
        mPhysicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
    }

    void PhysicsSystem::BeginContact(b2SensorBeginTouchEvent* contact)
    {
        Actor* sensorActor = reinterpret_cast<Actor*>(b2Shape_GetUserData(contact->sensorShapeId));
        Actor* visitorActor = reinterpret_cast<Actor*>(b2Shape_GetUserData(contact->visitorShapeId));

        if (sensorActor && !sensorActor->IsPendingDestruction()) {
            sensorActor->OnActorBeginOverlap(visitorActor);
        }

        if (visitorActor && !visitorActor->IsPendingDestruction()) {
            visitorActor->OnActorBeginOverlap(sensorActor);
        }
    }

    void PhysicsSystem::EndContact(b2SensorEndTouchEvent* contact)
    {
        Actor* sensorActor = nullptr;
        Actor* visitorActor = nullptr;

        if (b2Shape_IsValid(contact->sensorShapeId)) {
            sensorActor = reinterpret_cast<Actor*>(b2Shape_GetUserData(contact->sensorShapeId));
        }

        if (b2Shape_IsValid(contact->visitorShapeId)) {
            visitorActor = reinterpret_cast<Actor*>(b2Shape_GetUserData(contact->visitorShapeId));
        }

        if (sensorActor && !sensorActor->IsPendingDestruction()) {
            sensorActor->OnActorEndOverlap(visitorActor);
        }

        if (visitorActor && !visitorActor->IsPendingDestruction()) {
            visitorActor->OnActorEndOverlap(sensorActor);
        }
    }
}