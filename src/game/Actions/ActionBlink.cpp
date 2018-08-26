#include "ActionBlink.hpp"

ActionBlink::ActionBlink (DiamondPtr diamond, const float& timeDelta, float timeToBlink) :
    TimeAction(timeDelta), m_diamond(diamond), m_timeToBlink(timeToBlink), m_currentTime(0.f) {}

ActionBlink::~ActionBlink () {}

void ActionBlink::execute ()
{
    if (m_state == STATE::RUNNING)
    {
        m_currentTime += m_timeDelta;
        if (m_currentTime >= m_timeToBlink)
        {
            m_currentTime = 0.f;
            m_diamond->setRendeable(!m_diamond->getRendeable());
        }
    }
}

void ActionBlink::finish()
{
    m_diamond->setRendeable(true);
    m_state = STATE::FINISHED;
}