#pragma once
#include "framework/Delegate.h"

namespace ly {
    class HealthComponent {
    public:
        HealthComponent(float health, float maxHealth);
        void ChangeHealth(float amount);
        float GetHealth() const { return mHealth; }
        float GetMaxHealth() const { return mMaxHealth; }
        void SetInitalHealth(float health, float maxHealth);

        Delegate<float, float, float> onHealthChanged;
        Delegate<float, float, float> onTakenDamage;
        Delegate<> onHealthEmtpy;

    private:
        void TakeDamage(float amount);
        void HealthEmpty();
        float mHealth;
        float mMaxHealth;
    };
}