#ifndef __TIME_DECREASE_HPP__
#define __TIME_DECREASE_HPP__

#include <game/Actions/TimeAction.hpp>

class TimeDecrease : public TimeAction
{
    public:
                        TimeDecrease   (const float& timeDelta,
                                        float& time);
        virtual     ~TimeDecrease   () override;

        virtual void execute        ();

    protected:
        float& m_time;
};

#endif // !__TIME_DECREASE_H__