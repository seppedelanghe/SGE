#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <tuple>

#include "ECS.hpp"
#include "MapGenerator.hpp"
#include "IS/MapBuilder.hpp"
#include "Utils/noise.hpp"

std::runtime_error not_enough_tiles("You need at least 2 or more tile options to generate a map");

MapGenerator::MapGenerator()
{
}



void MapGenerator::addOption(int textureX, int textureY, int collision)
{
    tileOptions.push_back(std::make_tuple(textureX, textureY, collision));
}

// Generate pseudo random map using perlin noise
void MapGenerator::generate(MapBuilder* map, int w, int h)
{
    if (tileOptions.size() < 1) {
        throw not_enough_tiles;
    }

    srand(time(NULL));
    
    const int gridSize = w * h;
    
    float freq = 0.99f;
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            float x = j * freq;
            float y = i * freq;

            float noise = perlinNoise.Noise2D(x, y);    
            noise = (noise + 1) * 0.5f;
            printf("noise: %.7f, x: %.3f, y: %.3f\n", noise, x, y);

            int tileIdx = (int)(noise * (tileOptions.size() - 1));
            printf("tile %d\n", tileIdx);

            const auto[srcX, srcY, collision] = tileOptions[tileIdx];
            map->AddTile(srcX, srcY, x, y, Game::groupMap);

            if (collision > 0) {
                map->AddCollisionTile(x, y);
            }
        }
    }

    printf("Done here\n");
}
