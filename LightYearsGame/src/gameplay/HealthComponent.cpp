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

        if (amount < 0)
        {
            TakeDamage(amount);
            if (mHealth <= 0)
            {
                HealthEmpty();
            }
        }
        //else
        //{
        //    HealthRegen(amount);
        //}

        onHealthChanged.BroadCast(amount, mHealth, mMaxHealth);
    }

    void HealthComponent::TakeDamage(float amount)
    {
        onTakenDamage.BroadCast(amount, mHealth, mMaxHealth);
    }

    void HealthComponent::HealthEmpty()
    {
        onHealthEmtpy.BroadCast();
    }

    /*void HealthComponent::HealthRegen(float amount)
    {
        LOG("Healed %f, health now: %f from %f", amount, mHealth, mMaxHealth);
    }*/
}