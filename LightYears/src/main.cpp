#include "framework/Application.h"
#include <iostream>
#include <memory>

int main()
{
    // Allocating on the heap
    std::unique_ptr<ly::Application> app = std::make_unique<ly::Application>();
    app->Run();
}