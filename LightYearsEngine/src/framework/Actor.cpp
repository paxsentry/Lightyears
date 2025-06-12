#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetsManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath)
        :mOwningWorld{ owningWorld },
        mHasBeganPlay{ false },
        mSprite{ sf::Sprite::Sprite(GetEmptyTexture()) },
        mTexture{ },
        mPhysicsBody{ },
        mPhysicsEnabled{ false },
        mDebugRect{ }
    {
        SetTexture(texturePath);
    }

    Actor::~Actor()
    {
    }

    void Actor::BeginPlayInternal()
    {
        if (!mHasBeganPlay)
        {
            mHasBeganPlay = true;
            BeginPlay();
        }
    }

    void Actor::TickInternal(float deltaTime)
    {
        if (!IsPendingDestruction())
        {
            Tick(deltaTime);
        }
    }

    void Actor::BeginPlay()
    {
    }

    void Actor::Tick(float deltaTime)
    {
    }

    void Actor::SetTexture(const std::string& texturePath)
    {
        mTexture = AssetsManager::Get().LoadTexture(texturePath);

        if (!mTexture)
        {
            LOG("Invalid texture path: %s", texturePath.c_str());
            return;
        }

        mSprite.setTexture(*mTexture);

        int textureWidth = mTexture->getSize().x;
        int textureHeight = mTexture->getSize().y;

        mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
        CenterPivot();
    }

    void Actor::Render(sf::RenderWindow& window)
    {
        if (IsPendingDestruction()) return;

        window.draw(mSprite);
        window.draw(mDebugRect);
    }

    void Actor::SetActorLocation(const sf::Vector2f& newLoc)
    {
        mSprite.setPosition(newLoc);
        UpdatePhysicsBodyTransform();
    }

    void Actor::SetActorRotation(const float newRot)
    {
        sf::Angle newAngle = sf::degrees(newRot);
        SetActorRotation(newAngle);
    }

    void Actor::SetActorRotation(const sf::Angle& newRot)
    {
        mSprite.setRotation(newRot);
        UpdatePhysicsBodyTransform();
    }

    void Actor::AddActorLocationOffset(const sf::Vector2f& offset)
    {
        SetActorLocation(GetActorLocation() + offset);
    }

    void Actor::AddActorRotationOffset(const sf::Angle& offset)
    {
        SetActorRotation(GetActorRotation() + offset);
    }

    sf::Vector2f Actor::GetActorLocation() const
    {
        return mSprite.getPosition();
    }

    sf::Angle Actor::GetActorRotation() const
    {
        return mSprite.getRotation();
    }

    sf::Vector2f Actor::GetActorForwardDirection() const
    {
        return RotationToVector(GetActorRotation().asDegrees() - 90.f);
    }

    sf::Vector2f Actor::GetActorRightDirection() const
    {
        return RotationToVector(GetActorRotation().asDegrees());
    }

    sf::Vector2u Actor::GetWindowSize() const
    {
        return mOwningWorld->GetWindowSize();
    }

    void Actor::CenterPivot()
    {
        sf::FloatRect bound = mSprite.getGlobalBounds();
        mSprite.setOrigin(sf::Vector2f(bound.size.x / 2.f, bound.size.y / 2.f));
    }

    // This function is to create an empty texture, since SFML 3.0 there is NO cosntructor without texture
    const sf::Texture& Actor::GetEmptyTexture()
    {
        sf::RenderTexture renderTexture;
        sf::RectangleShape rect(sf::Vector2f(0.f, 0.f));

        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(rect);
        renderTexture.display(); 

        static sf::Texture texture = renderTexture.getTexture();

        return texture;
    }

    const void Actor::DrawDebugLines()
    {
        auto bounds = mSprite.getGlobalBounds();
        auto location = GetActorLocation();
        mDebugRect = sf::RectangleShape(sf::Vector2f(bounds.size.x, bounds.size.y));
        mDebugRect.setPosition(sf::Vector2f(location.x-bounds.size.x/2.f, location.y-bounds.size.y/2.f));
        
        mDebugRect.setOutlineColor(sf::Color::Red);
        mDebugRect.setFillColor(sf::Color::Transparent);
        mDebugRect.setOutlineThickness(2.f);
    }

    bool Actor::IsActorOutOfWindowBounds() const
    {
        float windowWidth = GetWorld()->GetWindowSize().x;
        float windowHeight = GetWorld()->GetWindowSize().y;

        float actorWidth = GetActorGlobalBounds().size.x;
        float actorHeight = GetActorGlobalBounds().size.y;

        sf::Vector2f actorPosition = GetActorLocation();

        if (actorPosition.x < -actorWidth)
        {
            return true;
        }

        if (actorPosition.x > windowWidth + actorWidth) 
        {
            return true;
        }

        if (actorPosition.y < -actorHeight)
        {
            return true;
        }

        if (actorPosition.y > windowHeight + actorHeight)
        {
            return true;
        }

        return false;
    }

    void Actor::InitPhysics()
    {
        if(!B2_IS_NON_NULL(mPhysicsBody)) {
           mPhysicsBody = PhysicsSystem::Get().AddListener(this);
        }
    }

    void Actor::UnInitPhysics()
    {
        if (B2_IS_NON_NULL(mPhysicsBody)) {
            PhysicsSystem::Get().RemoverListener(mPhysicsBody);
            mPhysicsBody = B2_ZERO_INIT;
        }
    }

    void Actor::SetEnablePhysics(bool enable)
    {
        mPhysicsEnabled = enable;

        if (mPhysicsEnabled) {
            InitPhysics();
        }
        else {
            UnInitPhysics();
        }
    }

    void Actor::Destroy()
    {
        UnInitPhysics();
        Object::Destroy();
    }

    void Actor::UpdatePhysicsBodyTransform()
    {
        if (B2_IS_NON_NULL(mPhysicsBody)) {
            
            float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
            b2Vec2 position{ GetActorLocation().x * physicsScale
                , GetActorLocation().y * physicsScale
            };
            b2Rot rotation = b2MakeRot(GetActorRotation().asRadians());

            b2Body_SetTransform(mPhysicsBody, position, rotation);
        }
    }

    void Actor::OnActorBeginOverlap(Actor* other)
    {
        LOG("Contact ");
    }

    void Actor::OnActorEndOverlap(Actor* other)
    {
        LOG("End contact");
    }

    sf::FloatRect Actor::GetActorGlobalBounds() const
    {
        return mSprite.getGlobalBounds();
    }
};