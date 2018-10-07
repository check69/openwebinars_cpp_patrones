#pragma once

#include <iostream>
#include <string>
#include <memory>

class Originator;

using namespace std;

class Memento
{
    public:
        ~Memento() {}

    private:
        friend class Originator;

                Memento(const string& state) : m_state(state) {}
        void    SetState(const string& state) { m_state = state; }
        string  GetState() { return m_state; }

        string m_state;
};

class Originator
{
    public:
                            Originator() {}
                            Originator(const string& state) : m_state(state) {}
                           ~Originator() {}
        void                RestoreToMemento(shared_ptr<Memento> pMemento) { m_state = pMemento->GetState(); }
        shared_ptr<Memento> CreateMemento() { return std::shared_ptr<Memento>(new Memento(m_state)); }
        void                SetState(const string& state) { m_state = state; }
        string              GetState() { return m_state; }
        void                showState() { cout << m_state << endl; }
    
    private:
        string m_state;
};

class Caretaker
{
    public:
                            Caretaker() : m_pMemento(nullptr) {}
                           ~Caretaker() {}
        void                SetMemento(shared_ptr<Memento> pMemento) { m_pMemento = pMemento; }
        shared_ptr<Memento> GetMemento() { return m_pMemento; }
    private:
        shared_ptr<Memento> m_pMemento;
};