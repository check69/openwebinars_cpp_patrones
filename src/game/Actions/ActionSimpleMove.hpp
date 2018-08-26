#ifndef __ACTIONSIMPLEMOVE_HPP__
#define __ACTIONSIMPLEMOVE_HPP__

#include <game/Actions/ActionBlockingStack.hpp>
#include <game/Actions/ActionMove.hpp>
#include <game/Actions/ActionStack.hpp>
#include <game/Actions/TimeAction.hpp>

#include <memory>

namespace testGame
{
    class ActionSimpleMove : public ActionBlockingStack
    {
        public:
            ActionSimpleMove(vec2& toMove1, vec2& toMove2, float& timedelta, float speed) :
                ActionBlockingStack(
                {
                    ActionPtr(
                        new ActionStack
                        {
                            ActionPtr(new ActionMove(toMove1, toMove2, timedelta, speed)),
                            ActionPtr(new ActionMove(toMove2, toMove1, timedelta, speed))
                        }),
                })
            {
            }

            virtual ~ActionSimpleMove() {}

        private:
            void    addAction           (ActionPtr action)  = delete;
                    ActionSimpleMove    ()                  = delete;
    };
}

#endif //!__ACTIONSIMPLEMOVE_HPP__