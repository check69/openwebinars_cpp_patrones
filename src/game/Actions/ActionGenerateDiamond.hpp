#ifndef __ACTIONS_GENERATE_DIAMOND_HPP__
#define __ACTIONS_GENERATE_DIAMOND_HPP__

#include <game/Diamond.hpp>
#include <game/Actions/Action.hpp>

#include <memory>

namespace testGame
{
    class ActionGenerateDiamond : public Action
    {
        public:
                            ActionGenerateDiamond   (std::shared_ptr<Diamond> diamond);
            virtual        ~ActionGenerateDiamond   ();
            virtual void    execute                 () override;

        protected:
            ActionGenerateDiamond() = delete;

            std::shared_ptr<Diamond> m_diamond;
    };

    using ActionGenerateDiamondPtr = std::shared_ptr<ActionGenerateDiamond>;
}

#endif