#pragma once

#include <memory>
#include <iostream>
#include <string>

class Basic
{
    public:
        virtual void pintar() = 0;
};

class BasicString : public Basic
{
    public:
    BasicString(const std::string& text) : m_text(text)
    {}

    void pintar () override
    {
        std::cout << m_text << std::endl;
    }

    private:
    std::string m_text;
};

class Decorator : public Basic
{
    public:
        Decorator(std::shared_ptr<Basic> basic) : m_basic(basic) {}

        virtual void pintar () override
        {
            m_basic->pintar();
        }

    private:
        std::shared_ptr<Basic> m_basic;
};

class BarraDecorator : public Decorator
{
    public:
        BarraDecorator(std::shared_ptr<Basic> basic) : Decorator(basic) {}

        virtual void pintar () override
        {
            Decorator::pintar();
            std::cout << "////" << std::endl;
        }
};
