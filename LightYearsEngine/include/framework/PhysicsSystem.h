#pragma once
#include "framework/Core.h"
#include <box2d/box2d.h>
#include <unordered_set>

// Hash for b2BodyId
bool operator==(b2BodyId const& lhs, b2BodyId const& rhs) {
    return (lhs.generation == rhs.generation) &&
        (lhs.index1 == rhs.index1) &&
        (lhs.world0 == rhs.world0);
}

class b2BodyIdHash {
public:
    size_t operator()(const b2BodyId& bodyId) const {
        return (std::hash<int32_t>()(bodyId.index1)) ^
            (std::hash<uint16_t>()(bodyId.world0)) ^
            (std::hash<uint16_t>()(bodyId.generation));
    }
};

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

        static void Cleanup();

    protected:
        PhysicsSystem();

    private:
        void ProcessPendingRemove();
        static unique<PhysicsSystem> mPhysicsSystem;
        b2Vec2 mGravity = { 0.0f, 0.0f };

        b2WorldDef mWorldDef = b2DefaultWorldDef();
        b2WorldId mPhysicsWorld;
        float mPhysicsScale; // to reduce Box2d meter based system, cm feels faster.
        int mSubStepCount;

        void BeginContact(b2SensorBeginTouchEvent* contact);
        void EndContact(b2SensorEndTouchEvent* contact);

        Set<b2BodyId> mPendingRemove;
    };
}
