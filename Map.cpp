#include "Map.hpp"
#include "Game.hpp"
#include <fstream>
#include "ECS/Components.hpp"

extern Manager manager;

Map::Map(std::string tId, int mscl, int tsize)
{
    texId = tId;
    mapScale = mscl;
    tileSize = tsize;

    scaledSize = mscl * tsize;
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int w, int h)
{
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            mapFile.get(c);
            srcY = atoi(&c) * tileSize;
            mapFile.get(c);
            srcX = atoi(&c) * tileSize;
            
            AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore(); // skip seperator
        }
    }

    mapFile.ignore();

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            mapFile.get(c);

            if (c == '1')
            {   
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.addGroup(Game::groupColliders);
            }
            mapFile.ignore();
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