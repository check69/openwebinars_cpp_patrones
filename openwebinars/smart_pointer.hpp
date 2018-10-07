#pragma once
#include <memory>
#include <iostream>

void smartPointers()
{
    int x = 3;
    std::weak_ptr<int> pw;
    std::shared_ptr<int> ps3{nullptr};
    {
        std::unique_ptr<int> pi = std::make_unique<int>(x);
        
        std::cout << "Unique " << *pi << std::endl;

        std::shared_ptr<int> ps1 = std::make_shared<int>(int(5));
        std::shared_ptr<int> ps2(ps1);
        ps3 = ps2;

        std::cout << "Shared " << *ps1 << " - " << *ps2 << std::endl;

        pw = ps3;
    }
    std::cout << "Shared " << *ps3 << std::endl;

    auto ps = pw.lock();
    if (ps != nullptr)
    {
        std::cout << "Weak " << *ps << std::endl;
    }
}