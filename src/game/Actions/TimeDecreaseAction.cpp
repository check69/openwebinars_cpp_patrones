#include "timeDecreaseAction.hpp"

namespace testGame
{
    TimeDecrease::TimeDecrease (const float& timeDelta,
                                float& time) :
        TimeAction(timeDelta),
        m_time(time)
    {
    }

    TimeDecrease::~TimeDecrease ()
    {
    }

    void TimeDecrease::execute ()
    {
        m_time -= m_timeDelta;

        if (m_time < 0)
        {
            m_state = STATE::FINISHED;
            m_time = 0;
        }
    }
}