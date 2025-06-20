#include "framework/TimerManager.h"

namespace ly
{
    unsigned int TimerHandle::mTimerKeyCounter = 0;

    TimerHandle::TimerHandle()
        :mTimerKey{ GetNextTimerKey() }
    {}

    bool operator==(const TimerHandle& lhs, const TimerHandle& rhs)
    {
        return lhs.GetTimerKey() == rhs.GetTimerKey();
    }

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

    void TimerManager::ClearTimer(TimerHandle timerHandle)
    {
        auto iter = mTimers.find(timerHandle);

        if (iter != mTimers.end())
        {
            iter->second.SetExpired();
        }
    }
}