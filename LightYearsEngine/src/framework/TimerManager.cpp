#include "framework/TimerManager.h"

namespace ly
{
    unique<TimerManager> TimerManager::mTimerManager{ nullptr };

    TimerManager::TimerManager()
    {}

    TimerManager& TimerManager::Get()
    {
        if (!mTimerManager)
        {
            mTimerManager = std::move(unique<TimerManager>(new TimerManager{}));
        }

        return *mTimerManager;
    }
}