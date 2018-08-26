#ifndef __ACTIONMOVE_HPP__
#define __ACTIONMOVE_HPP__

#include <game/Actions/TimeAction.hpp>
#include <utils/math.hpp>

namespace testGame
{
    class ActionMove : public TimeAction
    {
        public:
            ActionMove(vec2& movable, const vec2& destiny, const float& timeDelta, float speed) :
                TimeAction(timeDelta), m_2move(movable), m_destiny(destiny), m_speed(speed) {}

            virtual        ~ActionMove  () {}
            virtual void    execute     () override;

        protected:
            vec2& m_2move;
            vec2  m_destiny;
            float m_speed;

        private:
            ActionMove() = delete;
    };
}

#endif //!__ACTIONMOVE_HPP__