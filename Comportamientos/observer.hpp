#pragma once

#include <iostream>
#include <vector>
#include <memory>

class Observer
{
    public:
        virtual void notify() = 0;
};

class Subject
{
    public:
        Subject ()
        {}

        void addObserver(std::shared_ptr<Observer>&& observer)
        {
            m_vObservers.push_back(std::move(observer));
        }

        void notify()
        {
            for (auto& observer : m_vObservers)
                observer->notify();
        }

        void do_something()
        {
            std::cout << "do something" << std::endl;
            notify();
        }

    private:
        std::vector<std::shared_ptr<Observer>> m_vObservers;

};

class SubjectObserver : public Observer
{
    public:
        virtual void notify () override
        {
            std::cout << "He sido notificado, voy a hacer algo" << std::endl;
        }
};

class classObserver : public Observer
{
    public:
        virtual void notify () override
        {
            std::cout << "He sido notificado, voy a hacer algo" << std::endl;
        }
};