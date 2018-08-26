#ifndef __ACTIONSWAPMOVEDIAMOND_HPP__
#define __ACTIONSWAPMOVEDIAMOND_HPP__

#include <game/Actions/ActionCallable.hpp>
#include <game/Actions/ActionSwapMove.hpp>
#include <game/Diamond.hpp>

class ActionSwapMoveDiamond : public ActionBlockingStack
{
    public:
        ActionSwapMoveDiamond(const DiamondPtr& diamond1, const DiamondPtr& diamond2, float& timedelta,
                                float speed) :
            ActionBlockingStack(
            {
                ActionPtr(new ActionCallable(std::bind(&Diamond::dontAllowInteractive, diamond1))),
                ActionPtr(new ActionCallable(std::bind(&Diamond::dontAllowInteractive, diamond2))),
                /*ActionPtr(new ActionCallable([diamond1, diamond2]()
                {
                    diamond1->dontAllowInteractive();
                    diamond2->dontAllowInteractive();
                })),*/
                ActionPtr(new ActionSwapMove(diamond1->getPosition(), diamond2->getPosition(),
                                                timedelta, speed)),
                ActionPtr(new ActionCallable(std::bind(&Diamond::allowInteractive, diamond1))),
                ActionPtr(new ActionCallable(std::bind(&Diamond::allowInteractive, diamond2))),
                /*ActionPtr(new ActionCallable([diamond1, diamond2]()
                {
                    diamond1->allowInteractive();
                    diamond2->allowInteractive();
                })),*/
            })
        {
        }

        virtual ~ActionSwapMoveDiamond () {}

    private:
        void addAction          (ActionPtr action)  = delete;
        ActionSwapMoveDiamond   ()                  = delete;
};

using ActionSwapMoveDiamondPtr = std::shared_ptr<ActionSwapMoveDiamond>;

#endif    //!__ACTIONSWAPMOVEDIAMOND_HPP__