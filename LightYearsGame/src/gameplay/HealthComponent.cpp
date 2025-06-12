#include "gameplay/HealthComponent.h"
#include "framework/Core.h"

namespace ly {
    HealthComponent::HealthComponent(float health, float maxHealth)
        : mHealth {health},
        mMaxHealth{mMaxHealth}
    {
    }

    void HealthComponent::ChangeHealth(float amount)
    {
        if (amount == 0) return;
        if (mHealth == 0) return;

        mHealth += amount;

        if (mHealth < 0) {
            mHealth = 0;
        }

        if (mHealth > mMaxHealth) {
            mHealth = mMaxHealth;
        }

        if (amount < 0) {
            TakeDamage(amount);
            if (mHealth <= 0) {
                HealthEmpty();
            }
        }
        else
        {
            HealthRegen(amount);
        }
    }

    void HealthComponent::TakeDamage(float amount)
    {
        LOG("Took %f damage, health remain: %f from %f", amount, mHealth, mMaxHealth);
    }

    void HealthComponent::HealthEmpty()
    {
        LOG("Dead");
    }

    void HealthComponent::HealthRegen(float amount)
    {
        LOG("Healed %f, health now: %f from %f", amount, mHealth, mMaxHealth);
    }
}