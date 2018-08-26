#ifndef __ACTIONBLOCKINGSTACK_HPP__
#define __ACTIONBLOCKINGSTACK_HPP__

#include <game/Actions/ActionStack.hpp>

#include <initializer_list>
#include <list>

/*
The ACtionBlockingStack class represent a list of sequential actions to be computed
The execute method will run all the actions in the stack in order of inserting(FIFO), 
the consecutive actions will not be run till the previous ones are finished.
The stack will be finished once it has no more runnable actions inside.
*/

class ActionBlockingStack : public ActionStack
{
    public:
                        ActionBlockingStack ();
                        ActionBlockingStack (std::list<std::shared_ptr<Action>> actions);
                        ActionBlockingStack (std::initializer_list<std::shared_ptr<Action>> actions);
        virtual        ~ActionBlockingStack ();
        virtual void    execute             () override;
        virtual void    activateAll         () override;

    protected:
        void updateCurrent();

        std::shared_ptr<Action> m_currentAction;
};

using ActionBlockingStackPtr = std::shared_ptr<ActionBlockingStack>;

#endif    // !__ACTIONSTACK_H__