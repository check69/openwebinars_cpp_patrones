#ifndef __INITGRAPHICMAP_HPP__
#define __INITGRAPHICMAP_HPP__

#include <utils/math.hpp>

/*
The InitGraphicMap wraps the game data:
map width
map height
map rendering start position component X
map rendering start position component Y
map rendering end   position component X
map rendering end   position component Y
minimal size for matching
score per diamond crushed
*/

class InitGraphicMap
{
    public:
                        InitGraphicMap      (const unsigned uiWidth = 8, const unsigned uiHeight = 8,
                                                const float startPositionX = 330.f, const float startPositionY = 100.f,
                                                const float endPositionX = 680.f, const float endPositionY = 440.f,
                                                const unsigned int minMatch = 3, unsigned int score = 10,
                                                const float speedDiamond = 300, const float blinkDiamond = 0.2f);
        float           GetStartPositionX   ();
        float           GetStartPositionY   ();
        float           GetEndPositionX     ();
        float           GetEndPositionY     ();
        unsigned int    GetWidth            ();
        unsigned int    GetHeight           ();
        float           GetSizeX            ();
        float           GetSizeY            ();
        unsigned int    getMinMatch         ();
        vec2            getSpawnPosition    ();
        unsigned int    getScoreDiamond     ();
        float           getSpeedDiamond     ();
        float           getBlinkDiamond     ();

    private:
        float           m_sizeX;
        float           m_sizeY;
        unsigned int    m_width;
        unsigned int    m_height;
        float           m_startPositionX;
        float           m_startPositionY;
        float           m_endPositionX;
        float           m_endPositionY;
        unsigned int    m_minMatch;
        unsigned int    m_scoreDiamond;
        float           m_speedDiamond;
        float           m_blinkDiamond;
};

#endif // !__INITGRAPHICMAP_HPP_