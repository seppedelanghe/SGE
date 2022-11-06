#include "Map.hpp"
#include <fstream>

#include "../../Game.hpp"
#include "../C/Components.hpp"

extern Manager manager;

Map::Map(std::string tId, int mscl, int tsize)
{
    texId = tId;
    mapScale = mscl;
    tileSize = tsize;
    hasCollision = false;

    scaledSize = mscl * tsize;
}

Map::Map(std::string tId, int mscl, int tsize, bool hasCollisionMap)
{
    texId = tId;
    mapScale = mscl;
    tileSize = tsize;
    hasCollision = hasCollisionMap;

    scaledSize = mscl * tsize;
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int w, int h)
{
    char c[3];
    int srcIdx;

    std::fstream mapFile;
    mapFile.open(path);

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            mapFile.get(c, 4);
            srcIdx = atoi(c) * tileSize;
            
            AddTile(srcIdx, 0, x * scaledSize, y * scaledSize);
            mapFile.ignore(); // skip seperator
        }
    }


    if (hasCollision) {
        mapFile.ignore(); // newline
        char co;
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                mapFile.get(co);

                if (co == '1')
                {   
                    auto& tcol(manager.addEntity());
                    tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                    tcol.addGroup(Game::groupColliders);
                }
                mapFile.ignore();
            }
            
        }
    }

    mapFile.close();
}


void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texId);
    tile.addGroup(Game::groupMap);
}