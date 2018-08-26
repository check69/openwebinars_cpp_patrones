#ifndef __ACTIONUPGRADESCORE_HPP__
#define __ACTIONUPGRADESCORE_HPP__

#include <game/Actions/ActionPoints.hpp>

class ActionUpgradeScore : public ActionPoints
{
    public:
        ActionUpgradeScore  (unsigned int toIncrease, unsigned int& score) :
            ActionPoints(score), m_toIncrease(toIncrease)
        {
        }

        virtual        ~ActionUpgradeScore  () {}
        virtual void    execute             () override
        {
            if (m_state == STATE::RUNNING)
            {
                m_score += m_toIncrease;

                m_state = STATE::FINISHED;
            }
        }

    protected:
        unsigned int m_toIncrease;
        ActionUpgradeScore() = delete;
};

#endif //!__ACTIONUPGRADESCORE_HPP__