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
    unsigned int TimerManager::mTimerIndexCounter = 0;

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
        for (auto iter = mTimers.begin(); iter != mTimers.end(); )
        {
            if (iter->second.Expired())
            {
                iter = mTimers.erase(iter);
            }
            else
            {
                iter->second.TickTime(deltaTime);
                ++iter;
            }
        }
    }

    void TimerManager::ClearTimer(unsigned int timerIndex)
    {
        auto iter = mTimers.find(timerIndex);

        if (iter != mTimers.end())
        {
            iter->second.SetExpired();
        }
    }
}