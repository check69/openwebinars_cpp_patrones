#ifndef __TIME_ACTION_HPP__
#define __TIME_ACTION_HPP__

#include <game/Actions/Action.hpp>

#include <memory>

namespace testGame
{
    class TimeAction : public Action
    {
        public:
                            TimeAction  (const float& timeDelta) :
                                m_timeDelta(timeDelta) {}
            virtual        ~TimeAction  () override {}
            virtual void    execute     () override = 0;

        protected:
            const float& m_timeDelta;

        private:
            TimeAction () = delete;
    };
}

#endif // !__TIME_ACTION_H__
