#ifndef __ACTIONSWAPMOVE_HPP__
#define __ACTIONSWAPMOVE_HPP__

#include <game/Actions/ActionBlockingStack.hpp>
#include <game/Actions/ActionMove.hpp>
#include <game/Actions/ActionStack.hpp>
#include <game/Actions/TimeAction.hpp>

#include <memory>

namespace testGame
{
    class ActionSwapMove : public ActionBlockingStack
    {
        public:
            ActionSwapMove(vec2& toMove1, vec2& toMove2, float& timedelta, float speed) :
                ActionBlockingStack(
                {
                    ActionPtr(new ActionStack
                    {
                        ActionPtr(new ActionMove(toMove1, toMove2, timedelta, speed)),
                        ActionPtr(new ActionMove(toMove2, toMove1, timedelta, speed))
                    }),
                    ActionPtr(new ActionStack
                    {
                        ActionPtr(new ActionMove(toMove1, toMove1, timedelta, speed)),
                        ActionPtr(new ActionMove(toMove2, toMove2, timedelta, speed))
                    })
                })
            {
            }

        private:
            void addAction(std::shared_ptr<Action> action) = delete;
            ActionSwapMove()                               = delete;
    };
}

#endif    //!__ACTIONSWAPMOVE_HPP__