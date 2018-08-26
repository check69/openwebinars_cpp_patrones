#ifndef __ACTION_HPP__
#define __ACTION_HPP__

#include <memory>

class Action
{
public:
    enum class STATE
    {
        IDLE,
        RUNNING,
        FINISHED
    };

    Action          () : m_state(STATE::IDLE) {}
    virtual        ~Action          () {}
    virtual void    execute         () = 0;
    STATE           getState        () const { return m_state; }
    void            activate        () { m_state = STATE::RUNNING; }
    void            deactivate      () { m_state = STATE::IDLE; }
    virtual void    finish          () { m_state = STATE::FINISHED; }
    virtual void    activateAll     () { activate(); }
    virtual void    deactivateAll   () { deactivate(); }
    virtual void    finishAll       () { finish(); }

protected:
    STATE m_state;
};

using ActionPtr = std::shared_ptr<Action>;

#endif // !__ACTION_H__