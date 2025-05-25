#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG
    return "assets/";
#else
    return "F:/c++/LightYears/LightYearsGame/assets/";
#endif // NDEBUG
}
