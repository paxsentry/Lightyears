#pragma once
#include "framework/Core.h"
#include <box2d/box2d.h>
#include <unordered_set>

// Hash for b2BodyId
struct b2BodyIdHash {
    std::size_t operator()(const b2BodyId& bodyId) const noexcept {
        std::size_t h1 = std::hash<int32_t>()(bodyId.index1);
        std::size_t h2 = std::hash<uint16_t>()(bodyId.world0);
        std::size_t h3 = std::hash<uint16_t>()(bodyId.generation);

        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

struct b2BodyIdEqual {
    bool operator()(const b2BodyId& a, const b2BodyId& b) const noexcept {
        return a.index1 == b.index1 &&
            a.world0 == b.world0 &&
            a.generation == b.generation;
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

        std::unordered_set<b2BodyId, b2BodyIdHash, b2BodyIdEqual> mPendingRemove;
    };
}
