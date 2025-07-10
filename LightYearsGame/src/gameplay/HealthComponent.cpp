#include "framework/Core.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
    HealthComponent::HealthComponent(float health, float maxHealth)
        : mHealth{ health },
        mMaxHealth{ maxHealth }
    {}

    void HealthComponent::ChangeHealth(float amount)
    {
        if (amount == 0) return;
        if (mHealth == 0) return;

        mHealth += amount;

        if (mHealth < 0)
        {
            mHealth = 0;
        }

        if (mHealth > mMaxHealth)
        {
            mHealth = mMaxHealth;
        }

        onHealthChanged.BroadCast(amount, mHealth, mMaxHealth);

        if (amount < 0)
        {
            TakeDamage(amount);
            if (mHealth <= 0)
            {
                HealthEmpty();
            }
        }
    }

    void HealthComponent::SetInitalHealth(float health, float maxHealth)
    {
        mHealth = health;
        mMaxHealth = maxHealth;
    }

    void HealthComponent::TakeDamage(float amount)
    {
        onTakenDamage.BroadCast(amount, mHealth, mMaxHealth);
    }

    void HealthComponent::HealthEmpty()
    {
        onHealthEmtpy.BroadCast();
    }
}