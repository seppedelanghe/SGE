#include <cstdio>
#include <fstream>
#include <string.h>
#include <string>

#include "MapBuilder.hpp"
#include "../Game.hpp"
#include "../ECS/C/Components.hpp"

extern Manager manager;

MapBuilder::MapBuilder(std::string texture_id, float scale, int tile_size)
{
    textureId = texture_id;
    scaleFactor = scale;
    tileSize = tile_size;
    hasCollision = false;

    scaledSize = (int)(scale * (float)tile_size);
}

MapBuilder::MapBuilder(std::string texture_id, float scale, int tile_size, bool has_collision_map)
{
    textureId = texture_id;
    scaleFactor = scale;
    tileSize = tile_size;
    hasCollision = has_collision_map;

    scaledSize = (int)(scale * (float)tile_size);
}

MapBuilder::MapBuilder(std::string texture_id, float scale, int tile_size, bool has_collision_map, Game::groupLabels group)
{
    textureId = texture_id;
    scaleFactor = scale;
    tileSize = tile_size;
    hasCollision = has_collision_map;

    scaledSize = (int)(scale * (float)tile_size);
    renderGroup = group;
}



MapBuilder::~MapBuilder()
{
}

void MapBuilder::Fill(int texX, int texY, int w, int h, bool outerCollision)
{
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            AddTile(texX, texY, x, y, Game::groupMap);

            if (outerCollision) {
                if (x == 0 || x == w-1 || y == 0 || y == h-1) {
                    AddCollisionTile(x, y);
                }
            }
        }
    }
}

void MapBuilder::LoadMap(std::string path, int w, int h)
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

            AddTile(texture_x, texture_y, x, y, renderGroup);

            if (collisionLayer > 0) {
                AddCollisionTile(x, y);
            }

            mapFile.ignore(); // skip seperator
        }
    }

    mapFile.close();
}


void MapBuilder::AddTile(int srcX, int srcY, int xpos, int ypos, Game::groupLabels group)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX * tileSize, srcY * tileSize, xpos * scaledSize, ypos * scaledSize, tileSize, scaleFactor, textureId);
    tile.addGroup(group);
}

void MapBuilder::AddCollisionTile(int x, int y) {
    auto& tcol(manager.addEntity());
    tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
    tcol.addGroup(Game::groupColliders);
}
