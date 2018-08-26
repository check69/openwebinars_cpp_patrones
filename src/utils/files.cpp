#include "files.hpp"

#include <sstream>
#include <climits>
#include <fstream>
#include <vector>

using uint32 = unsigned int;

using namespace std;

namespace testGame
{
    std::string loadFile (const std::string& file)
    {
        std::string str;
        std::ifstream ifs(&file[0]);
        if (ifs.is_open())
        {
            // file length and reserve the memory.
            ifs.seekg(0, std::ios::end);
            str.reserve(static_cast<unsigned int>(ifs.tellg()));
            ifs.seekg(0, std::ios::beg);

            str.assign((std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()));

            ifs.close();
        }

        return str;
    }
}