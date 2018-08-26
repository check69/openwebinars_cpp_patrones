#ifndef __ACTIONBLINK_HPP__
#define __ACTIONBLINK_HPP__

#include <game/Actions/TimeAction.hpp>
#include <game/Diamond.hpp>
#include <utils/math.hpp>

class ActionBlink : public TimeAction
{
    public:
        ActionBlink(DiamondPtr diamond, const float& timeDelta, float timeToBlink);

        virtual        ~ActionBlink ();
        virtual void    execute     () override;
        virtual void    finish      ();

    protected:
        DiamondPtr m_diamond;
        float m_timeToBlink;
        float m_currentTime;

    private:
        ActionBlink() = delete;
};

#endif //!__ACTIONBLINK_HPP__