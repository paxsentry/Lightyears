#pragma once

namespace ly {
    class HealthComponent {
    public:
        HealthComponent(float health, float maxHealth);
        void ChangeHealth(float amount);
        float GetHealth() const { return mHealth; }
        float GetMaxHealth() const { return mMaxHealth; }

    private:
        void TakeDamage(float amount);
        void HealthEmpty();
        void HealthRegen(float amount);
        float mHealth;
        float mMaxHealth;
    };
}