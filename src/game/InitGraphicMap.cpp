#include "InitGraphicMap.hpp"

InitGraphicMap::InitGraphicMap(const unsigned uiWidth, const unsigned uiHeight,
                                const float startPositionX, const float startPositionY,
                                const float endPositionX, const float endPositionY,
                                const unsigned int minMatch, unsigned int score,
                                const float speedDiamond, const float blinkDiamond) :
    m_width(uiWidth),
    m_height(uiHeight),
    m_startPositionX(startPositionX),
    m_startPositionY(startPositionY),
    m_endPositionX(endPositionX),
    m_endPositionY(endPositionY),
    m_minMatch(minMatch),
    m_scoreDiamond(score),
    m_speedDiamond(speedDiamond),
    m_blinkDiamond(blinkDiamond)
{
    m_sizeX = (m_endPositionX - m_startPositionX) / m_width;
    m_sizeY = (m_endPositionY - m_startPositionY) / m_height;
}

float InitGraphicMap::GetStartPositionX()
{
    return m_startPositionX;
}

float InitGraphicMap::GetStartPositionY()
{
    return m_startPositionY;
}

float InitGraphicMap::GetEndPositionX()
{
    return m_endPositionX;
}

float InitGraphicMap::GetEndPositionY()
{
    return m_endPositionY;
}

unsigned int InitGraphicMap::GetWidth()
{
    return m_width;
}

unsigned int InitGraphicMap::GetHeight()
{
    return m_height;
}

float InitGraphicMap::GetSizeX()
{
    return m_sizeX;
}

float InitGraphicMap::GetSizeY()
{
    return m_sizeY;
}

unsigned int InitGraphicMap::getMinMatch()
{
    return m_minMatch;
}

vec2 InitGraphicMap::getSpawnPosition()
{
    return vec2(0.f, 350.f);
}

unsigned int InitGraphicMap::getScoreDiamond()
{
    return m_scoreDiamond;
}

float InitGraphicMap::getSpeedDiamond ()
{
    return m_speedDiamond;
}

float InitGraphicMap::getBlinkDiamond ()
{
    return m_blinkDiamond;
}