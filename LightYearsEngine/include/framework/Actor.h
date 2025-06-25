#pragma once
#include "Core.h"
#include "Object.h"
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

namespace ly
{
    class World;

    class Actor : public Object
    {
    public:
        Actor(World* owningWorld, const std::string& texturePath = "");
        virtual ~Actor();

        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
        void SetTexture(const std::string& texturePath);
        void Render(sf::RenderWindow& window);

        void SetActorLocation(const sf::Vector2f& newLoc);
        void SetActorRotation(const float newRot);
        void SetActorRotation(const sf::Angle& newRot);
        void SetActorScale(const sf::Vector2f& newScale);
        void AddActorLocationOffset(const sf::Vector2f& offset);
        void AddActorRotationOffset(const float newOffset);
        void AddActorRotationOffset(const sf::Angle& offset);

        sf::Vector2f GetActorLocation() const;
        sf::Angle GetActorRotation() const;
        sf::Vector2f GetActorForwardDirection() const;
        sf::Vector2f GetActorRightDirection() const;
        sf::Vector2u GetWindowSize() const;
        sf::FloatRect GetActorGlobalBounds() const;

        const World* GetWorld() const { return mOwningWorld; }
        World* GetWorld() { return mOwningWorld; }
        const void DrawDebugLines();

        bool IsActorOutOfWindowBounds(float allowance = 10.f) const;

        void SetEnablePhysics(bool enable);
        virtual void OnActorBeginOverlap(Actor* other);
        virtual void OnActorEndOverlap(Actor* other);
        virtual void Destroy() override;

        static uint8 GetNeutralTeamId() { return neutralTeamId; }
        void SetTeamId(uint8 teamId) { mTeamId = teamId; }
        uint8 GetTeamId() const { return mTeamId; }
        bool IsOtherHostile(Actor* other) const;

        virtual void ApplyDamage(float amount);

        sf::Sprite& GetSprite() { return mSprite; }
        const sf::Sprite& GetSprite() const { return mSprite; }

    private:
        void CenterPivot();
        void InitPhysics();
        void UnInitPhysics();
        void UpdatePhysicsBodyTransform();

        World* mOwningWorld;

        bool mHasBeganPlay;

        sf::Sprite mSprite;
        shared<sf::Texture> mTexture;
        const sf::Texture& GetEmptyTexture();

        b2BodyId mPhysicsBody;
        bool mPhysicsEnabled;
        sf::RectangleShape mDebugRect;

        uint8 mTeamId;

        const static uint8 neutralTeamId = 255;
    };
}