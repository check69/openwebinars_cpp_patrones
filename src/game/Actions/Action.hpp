#ifndef __ACTION_HPP__
#define __ACTION_HPP__

#include <memory>

/*
Action is the base abstract class for all controlling operations
An action should implement execute, where all the computation should be done
All variables needed to operate with must be provided within the constructor of 
any Action class
In case an Action contains other actions the interfaces %(activate, deactivate, finish)
All are provide 
*/

class Action
{
    public:
        enum class STATE
        {
            IDLE,
            RUNNING,
            FINISHED
        };

                        Action          () : m_state(STATE::IDLE)      {}
        virtual        ~Action          () {}
        virtual void    execute         () = 0;
        STATE           getState        () const { return m_state;      }
        void            activate        () { m_state = STATE::RUNNING;  }
        void            deactivate      () { m_state = STATE::IDLE;     }
        virtual void    finish          () { m_state = STATE::FINISHED; }
        virtual void    activateAll     () { activate();                }
        virtual void    deactivateAll   () { deactivate();              }
        virtual void    finishAll       () { finish();                  }

    protected:
        STATE m_state;
};

using ActionPtr = std::shared_ptr<Action>;

#endif    // !__ACTION_H__
