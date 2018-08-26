#include "ActionMove.hpp"
#include <cmath>

void testGame::ActionMove::execute()
{
    if (m_state == STATE::RUNNING)
    {
        vec2  dir    = m_destiny - m_2move;
        float length = sqrtf(pow(dir.x, 2) + pow(dir.y, 2));
        vec2  tomove = vec2(dir.x / abs(length), dir.y / abs(length)) * (m_timeDelta * m_speed);
        m_2move += tomove;
    }
    vec2 leftMove = m_2move - m_destiny;
    if (abs(leftMove.x) <= m_speed * m_timeDelta &&
        abs(leftMove.y) <= m_speed * m_timeDelta)
    {
        m_2move = m_destiny;
        m_state = STATE::FINISHED;
    }
}