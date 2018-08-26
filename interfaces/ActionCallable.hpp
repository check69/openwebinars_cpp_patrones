#ifndef __ACTIONCALLABLE_HPP__
#define __ACTIONCALLABLE_HPP__

#include "Action.hpp"

#include <functional>


class ActionCallable : public Action
{
    public:
                        ActionCallable  (std::function<void()> method) : m_funtion(method) {}
                       ~ActionCallable  () {} 
        virtual void    execute         () override
        {
            if (m_state == STATE::RUNNING)
            {
                m_funtion();
                m_state = STATE::FINISHED;
            }
        }

    protected:
        std::function<void()> m_funtion;

    private:
        ActionCallable() = delete;
};

#endif // !__ACTIONCALLABLE_HPP__