#pragma once
#include "Core.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

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
        void AddActorLocationOffset(const sf::Vector2f& offset);
        void AddActorRotationOffset(const sf::Angle& offset);

        sf::Vector2f GetActorLocation() const;
        sf::Angle GetActorRotation() const;
        sf::Vector2f GetActorForwardDirection() const;
        sf::Vector2f GetActorRightDirection() const;
        sf::Vector2u GetWindowSize() const;
        sf::FloatRect GetActorGlobalBounds() const;

        World* GetWorld() const { return mOwningWorld; }
        const void DrawDebugLines();

        bool IsActorOutOfWindowBounds() const;

        void SetEnablePhysics(bool enable);
        virtual void OnActorBeginOverlap(Actor* other);
        virtual void OnActorEndOverlap(Actor* other);
        virtual void Destroy() override;

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
    };
}