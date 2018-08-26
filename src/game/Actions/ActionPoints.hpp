#ifndef __ACTIONSPOINTS_HPP__
#define __ACTIONSPOINTS_HPP__

#include <game/Actions/Action.hpp>

#include <memory>

class ActionPoints : public Action
{
public:
    ActionPoints    (unsigned int& score) : m_score(score) {}
    virtual        ~ActionPoints    () {}
    virtual void    execute         () override = 0;

protected:
    unsigned int& m_score;

private:
    ActionPoints    () = delete;
};

#endif //!__ACTIONSPOINTS_HPP__