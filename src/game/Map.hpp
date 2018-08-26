#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <game/Diamond.hpp>
#include <game/InitGraphicMap.hpp>
#include <utils/math.hpp>

#include <vector>

/*
Map represent the game grid, the logical grid where the diamond are stores 
as well as the physical positions of the grid and the respawn physical positions.
*/

class Map
{
    public:
        Map();

        DiamondPtr              getCell         (unsigned int column,unsigned int row);
        void                    setElement      (unsigned int column,unsigned int row,DiamondPtr d);
        vec2                    getCellPos      (unsigned int column,unsigned int row);
        vec2                    getCellSpawnPos (unsigned int column,unsigned int row);
        std::vector<DiamondPtr> getColumn       (unsigned int column);
        std::vector<DiamondPtr> getRow          (unsigned int row);

    private:
        std::vector<std::vector<DiamondPtr>>    m_map;
        std::vector<std::vector<vec2>>          m_positions;
        std::vector<std::vector<vec2>>          m_spawnPositions;
        InitGraphicMap                          m_initGraphicMap;
};

#endif //!__MAP_HPP__