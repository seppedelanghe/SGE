#include <fstream>
#include <string.h>

#include "Map.hpp"
#include "../../Game.hpp"
#include "../C/Components.hpp"

extern Manager manager;

Map::Map(std::string texture_id, float scale, int tile_size)
{
    textureId = texture_id;
    scaleFactor = scale;
    tileSize = tile_size;
    hasCollision = false;

    scaledSize = scale * tile_size;
}

Map::Map(std::string texture_id, float scale, int tile_size, bool has_collision_map)
{
    textureId = texture_id;
    scaleFactor = scale;
    tileSize = tile_size;
    hasCollision = has_collision_map;

    scaledSize = (int)(scale * (float)tile_size);
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int w, int h)
{
    char c[6];
    int texture_x;
    int texture_y;
    int collisionLayer;

    std::fstream mapFile;
    mapFile.open(path);

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            mapFile.get(c, 6);
            
            texture_x = c[0] - '0';
            texture_y = c[2] - '0';
            collisionLayer = c[4] - '0';

            AddTile(texture_x * tileSize, texture_y * tileSize, x * scaledSize, y * scaledSize);

            if (collisionLayer > 0) {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.addGroup(Game::groupColliders);
            }

            mapFile.ignore(); // skip seperator
        }
    }

    mapFile.close();
}


void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, scaleFactor, textureId);
    tile.addGroup(Game::groupMap);
}
