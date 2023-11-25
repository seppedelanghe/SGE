#ifndef MapGenerator_hpp
#define MapGenerator_hpp

#include <map>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#include "IS/MapBuilder.hpp"

class MapGenerator {
    private:
        std::vector<std::tuple<int, int, int>> tileOptions;

    public:
        MapGenerator();

        void addOption(int textureX, int textureY, int collision);
        void generate(MapBuilder* map, int w, int h);
};

#endif /* MapGenerator_hpp */
