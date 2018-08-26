#include "ActionBlockingStack.hpp"

namespace testGame
{
ActionBlockingStack::ActionBlockingStack() : ActionStack(), m_currentAction(nullptr) {}
ActionBlockingStack::ActionBlockingStack(std::list<std::shared_ptr<Action>> actions)
    : ActionStack(actions), m_currentAction(actions.front())
{
}

ActionBlockingStack::ActionBlockingStack(std::initializer_list<std::shared_ptr<Action>> actions)
    : ActionStack(actions), m_currentAction(m_actions.front())
{
}

ActionBlockingStack::~ActionBlockingStack() {}
void ActionBlockingStack::activateAll()
{
    ActionStack::activateAll();

    if (m_actions.size())
    {
        m_currentAction = m_actions.front();
    }
}

void ActionBlockingStack::execute()
{
    if (m_currentAction != nullptr)
    {
        switch (m_currentAction->getState())
        {
            case Action::STATE::RUNNING:
            {
                m_currentAction->execute();
                break;
            }
            case Action::STATE::FINISHED:
            {
                updateCurrent();
                break;
            }
            default:
                break;
        }
    }
    if (!m_actions.size()) m_state = STATE::FINISHED;
}

void ActionBlockingStack::updateCurrent()
{
    m_actions.pop_front();
    if (m_actions.size())
    {
        m_currentAction = m_actions.front();
    }
    else
    {
        m_currentAction = nullptr;
        m_state         = STATE::FINISHED;
    }
}
}