#include "Map.hpp"

Map::Map () :
    m_map(),
    m_positions(),
    m_spawnPositions(),
    m_initGraphicMap()
{
    m_map.resize(m_initGraphicMap.GetWidth());
    m_positions.resize(m_initGraphicMap.GetWidth());
    m_spawnPositions.resize(m_initGraphicMap.GetWidth());
    for (auto& column: m_map)
    {
        column.resize(m_initGraphicMap.GetHeight());
    }
    for(auto& column: m_positions)
    {
        column.resize(m_initGraphicMap.GetHeight());
    }
    for(auto& column: m_spawnPositions)
    {
        column.resize(m_initGraphicMap.GetHeight());
    }

    for (unsigned int column = 0; column < m_initGraphicMap.GetWidth(); ++column)
    {
        float xpos = m_initGraphicMap.GetStartPositionX() + m_initGraphicMap.GetSizeX()*column;
        for(unsigned int row = 0; row < m_initGraphicMap.GetWidth(); ++row)
        {
            float ypos = m_initGraphicMap.GetStartPositionY() + m_initGraphicMap.GetSizeY()*row;
            vec2 position(xpos, ypos);

            m_positions[column][row] = position;
            m_spawnPositions[column][row] = position - m_initGraphicMap.getSpawnPosition();
        }
    }
}

DiamondPtr Map::getCell(unsigned int column,unsigned int row)
{
    if(column >= m_initGraphicMap.GetWidth() || row >= m_initGraphicMap.GetHeight())
    {
        return nullptr;
    }

    return m_map[column][row];
}

void Map::setElement(unsigned int column,unsigned int row, DiamondPtr d)
{
    if(column >= m_initGraphicMap.GetWidth() || row >= m_initGraphicMap.GetHeight())
    {
        return;
    }

    m_map[column][row] = d;
}

vec2 Map::getCellPos(unsigned int column,unsigned int row)
{
    if(column >= m_initGraphicMap.GetWidth() || row >= m_initGraphicMap.GetHeight())
    {
        return vec2(0, 0);
    }

    return m_positions[column][row];
}

vec2 Map::getCellSpawnPos(unsigned int column,unsigned int row)
{
    if(column >= m_initGraphicMap.GetWidth() || row >= m_initGraphicMap.GetHeight())
    {
        return vec2(0,0);
    }

    return m_spawnPositions[column][row];
}

std::vector<DiamondPtr> Map::getRow(unsigned int row)
{
    std::vector<DiamondPtr> ret{};
    if (row >= m_initGraphicMap.GetWidth())
    {
        return ret;
    }

    for (unsigned int i = 0; i < m_initGraphicMap.GetWidth(); ++i)
    {
        ret.push_back(m_map[i][row]);
    }

    return ret;
}

std::vector<DiamondPtr> Map::getColumn(unsigned int column)
{
    std::vector<DiamondPtr> ret{};
    if(column >= m_initGraphicMap.GetHeight())
    {
        return ret;
    }

    return m_map[column];
}