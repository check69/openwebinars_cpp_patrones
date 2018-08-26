#include "Diamond.hpp"

#include <limits>

Diamond::Diamond () :
    m_position(0.f, 0.f),
    m_bInteractive(true),
    m_active(true),
    m_rendeable(true),
    m_uiTexture(std::numeric_limits<unsigned>::max())
{
}

Diamond::~Diamond ()
{
}