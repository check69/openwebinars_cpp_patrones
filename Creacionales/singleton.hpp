#pragma once

#include <memory>
#include <iostream>

class Singleton
{
    public:
    static std::shared_ptr<Singleton> getInstance()
    {
        if (!m_pSingleton)
        {
            m_pSingleton = std::make_shared<Singleton>(Singleton());
        }

        return m_pSingleton;
    }

    void func ()
    {
        std::cout << "Hola, soy un singleton";
    }

    private:
     Singleton () {}
     

     static std::shared_ptr<Singleton> m_pSingleton;
};

std::shared_ptr<Singleton> Singleton::m_pSingleton(nullptr);