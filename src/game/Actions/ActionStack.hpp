#ifndef __ACTIONSTACK_HPP__
#define __ACTIONSTACK_HPP__

#include <game/Actions/Action.hpp>

#include <initializer_list>
#include <list>
#include <memory>

/*
The ActionStack class represent a list of concurrent actions to be computed
The execute method will run all the actions in the stack.  
The stack will be finished once it has no more runnable actions inside.
*/

class ActionStack : public Action
{
    public:
                        ActionStack     ();
                        ActionStack     (std::list<std::shared_ptr<Action>>& actions);
                        ActionStack     (std::initializer_list<std::shared_ptr<Action>> actions);
        virtual        ~ActionStack     ();
        virtual void    execute         () override;
                void    addAction       (std::shared_ptr<Action> action);
        virtual void    activateAll     ();
        virtual void    deactivateAll   ();
        virtual void    finishAll       ();
                void    cleanUp         ();

    protected:
        std::list<std::shared_ptr<Action>> m_actions{};
};

using ActionStackPtr = std::shared_ptr<ActionStack>;

#endif // !__ACTIONSTACK_H__