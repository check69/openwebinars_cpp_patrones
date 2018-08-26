#ifndef __DIAMOND_HPP__
#define __DIAMOND_HPP__

#include <utils/math.hpp>
#include <memory>

class Diamond
{
    public:
                        Diamond                 ();
                        ~Diamond                 ();

        void            setTexture              (unsigned int id)               { m_uiTexture = id;         }
        void            setPosition             (const vec2& position)          { m_position = position;    }
        vec2&           getPosition             ()                              { return m_position;        }
        unsigned int&   getTexture              ()                              { return m_uiTexture;       }
        void            allowInteractive        ()                              { m_bInteractive = true;    }
        void            dontAllowInteractive    ()                              { m_bInteractive = false;   }
        bool            isInteractive           ()                              { return m_bInteractive;    }
        bool            isActive                ()                      const   { return m_active;          }
        void            setActive               (bool active)                   { m_active = active;        }
        bool&           getRendeable            ()                              { return m_rendeable;       }
        bool            isRendeable             ()                      const   { return m_rendeable;       }
        void            setRendeable            (bool rendeable)                { m_rendeable = rendeable;  }

        bool operator==(const Diamond* other) const { return this->m_uiTexture == other->m_uiTexture;  };
        void operator= (const Diamond& other)
        {
            m_uiTexture     = other.m_uiTexture;
            m_bInteractive  = other.m_bInteractive;
            m_position      = other.m_position;
        }


    private:
        vec2            m_position;
        bool            m_bInteractive;
        bool            m_active;
        bool            m_rendeable;
        unsigned int    m_uiTexture;
};

using DiamondPtr = std::shared_ptr<Diamond>;

#endif //!__DIAMOND_HPP__