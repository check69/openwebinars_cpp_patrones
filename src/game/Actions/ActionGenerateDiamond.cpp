#include "ActionGenerateDiamond.hpp"

#include <graphic/Engine.h>
#include <randomWrapper/random.hpp>

namespace testGame
{
    using Random = effolkronium::random_static;

    ActionGenerateDiamond::ActionGenerateDiamond(std::shared_ptr<Diamond> diamond): m_diamond(diamond)
    {
    }

    ActionGenerateDiamond::~ActionGenerateDiamond() {}
    void ActionGenerateDiamond::execute()
    {
        if(!m_diamond)
        {
            m_diamond.reset(new Diamond());
        }

        m_diamond->setTexture(Random::get(static_cast<unsigned>(Engine::TEXTURE_BLUE),
                              static_cast<unsigned>(Engine::TEXTURE_YELLOW)));

        finish();
    }
}