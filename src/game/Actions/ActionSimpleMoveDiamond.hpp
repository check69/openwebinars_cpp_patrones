#ifndef __ACTIONSIMPLEMOVEDIAMOND_HPP__
#define __ACTIONSIMPLEMOVEDIAMOND_HPP__

#include <functional>
#include <vector>

#include <game/Actions/ActionCallable.hpp>
#include <game/Actions/ActionSimpleMove.hpp>
#include <game/Diamond.hpp>

namespace testGame
{
    class ActionSimpleMoveDiamond : public ActionBlockingStack
    {
        public:
            ActionSimpleMoveDiamond(const DiamondPtr& diamond1,
                                    const DiamondPtr& diamond2,
                                    float& timedelta,
                                    float speed) :
                ActionBlockingStack(
                {
                    ActionPtr(new ActionCallable(std::bind(&Diamond::dontAllowInteractive, diamond1))),
                    ActionPtr(new ActionCallable(std::bind(&Diamond::dontAllowInteractive, diamond2))),
                    ActionPtr(new ActionSimpleMove(diamond1->getPosition(),
                                                   diamond2->getPosition(),
                                                   timedelta, speed)),
                    ActionPtr(new ActionCallable(std::bind(&Diamond::allowInteractive, diamond1))),
                    ActionPtr(new ActionCallable(std::bind(&Diamond::allowInteractive, diamond2))),
                })
            {
            }

            virtual ~ActionSimpleMoveDiamond() {}

        private:
            void addAction(ActionPtr action) = delete;
            ActionSimpleMoveDiamond()        = delete;
    };

    using ActionSimpleMoveDiamondPtr = std::shared_ptr<ActionSimpleMoveDiamond>;
}

#endif    //!__ACTIONSIMPLEMOVEDIAMOND_HPP__