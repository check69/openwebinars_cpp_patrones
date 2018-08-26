#ifndef __ACTIONCALLABLE_HPP__
#define __ACTIONCALLABLE_HPP__

#include <game/Actions/Action.hpp>

#include <functional>

/*
ActionCallable represents a generic computation wrapped inside an action
The ActionCallable will run the function passed as argument and finish himself.
*/

namespace testGame
{
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
}

#endif    // !__ACTIONCALLABLE_HPP__