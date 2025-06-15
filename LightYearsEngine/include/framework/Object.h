#pragma once
#include <memory>
#include "framework/Core.h"

namespace ly
{
    class Object : public std::enable_shared_from_this<Object>
    {
    public:
        Object();
        virtual ~Object();

        virtual void Destroy();

        bool IsPendingDestruction() const {
            return mIsPedingDestruction;
        }

        weak<Object> GetSelfWeakRef();

    private:
        bool mIsPedingDestruction;
    };
}