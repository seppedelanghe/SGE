#include "Map.hpp"
#include "Game.hpp"
#include <fstream>

Map::Map()
{
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int w, int h)
{
    char tile;
    std::fstream mapFile;
    mapFile.open(path);

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            mapFile.get(tile);
            Game::AddTile(atoi(&tile), x * 32, y * 32);
            mapFile.ignore(); // skip seperator
        }
    }


    mapFile.close();
}
