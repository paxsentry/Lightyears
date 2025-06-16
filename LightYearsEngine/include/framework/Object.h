#pragma once
#include "framework/Core.h"
#include "framework/Delegate.h"
#include <memory>

namespace ly
{
    class Object : public std::enable_shared_from_this<Object>
    {
    public:
        Object();
        virtual ~Object();

        virtual void Destroy();

        bool IsPendingDestruction() const
        {
            return mIsPedingDestruction;
        }

        weak<Object> GetWeakRef();
        weak<const Object>GetWeakRef() const;
        Delegate<Object*> onDestroy;

    private:
        bool mIsPedingDestruction;
    };
}