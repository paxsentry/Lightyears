#pragma once
#include "framework/Core.h"
#include "framework/Object.h"
#include <functional>

namespace ly
{
    struct Timer
    {
    public:
        Timer(weak<Object> weakref, std::function<void()> callback, float duration, bool repeat);
        void TickTime(float deltaTime);
        bool Expired() const;
        void SetExpired();

    private:
        std::pair<weak<Object>, std::function<void()>> mListener;
        float mDuration;
        bool mRepeat;
        float mTimeCounter;
        bool mIsExpired;
    };

    class TimerManager
    {
    public:
        static TimerManager& Get();

        template<typename ClassName>
        unsigned int SetTimer(weak<Object> weakRef, void(ClassName::* callback)(), float duration, bool repeat = false)
        {
            ++mTimerIndexCounter;
            mTimers.insert({
                mTimerIndexCounter,
                Timer(
                    weakRef,
                    [=] { (static_cast<ClassName*>(weakRef.lock().get())->*callback)(); },
                    duration,
                    repeat)
                });

            return mTimerIndexCounter;
        };

        void UpdateTimer(float deltaTime);
        void ClearTimer(unsigned int timerIndex);

    protected:
        TimerManager();

    private:
        static unique<TimerManager> mTimerManager;
        static unsigned int mTimerIndexCounter;
        Dictionary<unsigned int, Timer> mTimers;
    };
}