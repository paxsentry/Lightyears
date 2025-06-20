#include "framework/TimerManager.h"

namespace ly
{

    Timer::Timer(weak<Object> weakref, std::function<void()> callback, float duration, bool repeat) :
        mListener{ weakref, callback },
        mDuration{ duration },
        mRepeat{ repeat },
        mTimeCounter{ 0 },
        mIsExpired{ false }
    {}

    void Timer::TickTime(float deltaTime)
    {
        if (Expired()) { return; }

        mTimeCounter += deltaTime;

        if (mTimeCounter >= mDuration)
        {
            mListener.second();

            if (mRepeat)
            {
                mTimeCounter = 0.f;
            }
            else
            {
                SetExpired();
            }
        }
    }

    bool Timer::Expired() const
    {
        return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestruction();
    }

    void Timer::SetExpired()
    {
        mIsExpired = true;
    }

    unique<TimerManager> TimerManager::mTimerManager{ nullptr };

    TimerManager::TimerManager()
        :mTimers{}
    {}

    TimerManager& TimerManager::Get()
    {
        if (!mTimerManager)
        {
            mTimerManager = std::move(unique<TimerManager>(new TimerManager{}));
        }

        return *mTimerManager;
    }

    void TimerManager::UpdateTimer(float deltaTime)
    {
        for (Timer& timer : mTimers)
        {
            timer.TickTime(deltaTime);
        }
    }
}