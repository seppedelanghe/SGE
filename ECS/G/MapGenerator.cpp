
#include "G/MapGenerator.hpp"
#include "A/Map.hpp"
#include "ECS.hpp"
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <tuple>
#include "../utils/noise.cpp"

std::runtime_error not_enough_tiles("You need at least 2 or more tile options to generate a map");

MapGenerator::MapGenerator()
{
}



void MapGenerator::addOption(int textureX, int textureY, int collision)
{
    tileOptions.push_back(std::make_tuple(textureX, textureY, collision));
}

// Generate pseudo random map using perlin noise
void MapGenerator::generate(Map* map, int w, int h)
{
    if (tileOptions.size() < 1) {
        throw not_enough_tiles;
    }

    srand(time(NULL));
    
    int gridSize = w * h;
    float max = 0.0f;
    float* values = new float[gridSize]();
    
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            float val = 0;
            float freq = 1;
            float amp = 1;
            int n_samples = 8;

            for (int i = 0; i < n_samples; i++) {
                val += perlin(x * freq / gridSize, y * freq / gridSize) * amp;

                freq *= 2;
                amp /= 2;
            }
            
            // contrast
            val *= 1.2;

            if (val > max) {
                max = val;
            }
            
            values[x*y] = val;
        }
    }


    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            float val = values[x*y];
            // between 0 - 1
            val = val / max;

            int tileIdx = (int)(val * (tileOptions.size() - 1));
            const auto[srcX, srcY, collision] = tileOptions[tileIdx];
            map->AddTile(srcX, srcY, x, y, Game::groupMap);

            if (collision > 0) {
                map->AddCollisionTile(x, y);
            }
            
        }
        
    }
}
