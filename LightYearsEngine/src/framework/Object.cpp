#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
    Object::Object()
        :mIsPedingDestruction{ false }
    {}

    Object::~Object()
    {}

    void Object::Destroy()
    {
        onDestroy.BroadCast(this);
        mIsPedingDestruction = true;
    }

    weak<Object> Object::GetWeakRef()
    {
        return weak_from_this();
    }

    weak<const Object> Object::GetWeakRef() const
    {
        return weak_from_this();
    }
}