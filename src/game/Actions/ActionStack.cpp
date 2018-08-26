#include "ActionStack.hpp"

#include <functional>

ActionStack::ActionStack() : Action() {}
ActionStack::ActionStack(std::list<std::shared_ptr<Action>>& actions) : m_actions(actions) {}
ActionStack::ActionStack(std::initializer_list<std::shared_ptr<Action>> actions)
    : m_actions(actions)
{
}

ActionStack::~ActionStack() { m_actions.clear(); }
void ActionStack::execute()
{
    for (auto& a : m_actions)
    {
        a->execute();
    }

    cleanUp();

    if (!m_actions.size())
    {
        m_state = STATE::FINISHED;
    }
}

void ActionStack::addAction(std::shared_ptr<Action> action) { m_actions.push_back(action); }
void                                                ActionStack::activateAll()
{
    activate();
    for (auto& a : m_actions)
    {
        a->activateAll();
    }
}

void ActionStack::deactivateAll()
{
    deactivate();
    for (auto& a : m_actions)
    {
        a->deactivateAll();
    }
}

void ActionStack::finishAll()
{
    finish();
    for (auto& a : m_actions)
    {
        a->finishAll();
    }
}
void ActionStack::cleanUp()
{
    m_actions.remove_if([](auto& action) { return action->getState() == Action::STATE::FINISHED; });
}