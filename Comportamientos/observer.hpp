#pragma once

#include <memory>
#include <iostream>
#include <vector>

class Observer
{
    public:
        virtual void notify() = 0;
};

class Subject
{
    public:
        Subject() {}

        void addObserver(std::shared_ptr<Observer> observer)
        {
            m_vObservers.push_back(observer);
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
        virtual void notify()
        {
            std::cout << "He sido notificado soy subjectObserver, voy a hacer algo" << std::endl;
        }
};

class ClassObserver : public Observer
{
    public:
    virtual void notify()
    {
        std::cout << "He sido notificado soy classObserver, no me interesa" << std::endl;
    }
};