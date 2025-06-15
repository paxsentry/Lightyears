#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
    Object::Object()
        :mIsPedingDestruction{ false }
    {
    }

    Object::~Object()
    {
        LOG("Object destructed");
    }

    void Object::Destroy()
    {
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