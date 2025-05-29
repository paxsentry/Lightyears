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
        //LOG("Object destructed");
    }

    void Object::Destroy()
    {
        mIsPedingDestruction = true;
    }
}