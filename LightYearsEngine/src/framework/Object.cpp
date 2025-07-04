#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
    unsigned int Object::mUniqueIdCounter = 0;

    Object::Object()
        :mIsPedingDestruction{ false },
        mUniqueId{ GetNextAvailableId() }
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

    unsigned int Object::GetNextAvailableId()
    {
        return mUniqueIdCounter++;
    }
}