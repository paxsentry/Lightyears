#include <stdio.h>
#include <memory>

namespace ly
{
    #define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}