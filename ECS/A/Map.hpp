#pragma once

#include <string>

class Map
{
    public:
        Map(std::string texture_id, float scale, int tile_size);
        Map(std::string texture_id, float scale, int tile_size, bool has_collision_map);
        ~Map();

        void LoadMap(std::string path, int w, int h);
        void AddTile(int srcX, int srcY, int xpos, int ypos);

    private:
        std::string textureId;
        bool hasCollision;
        float scaleFactor;
        int tileSize;
        int scaledSize;
};
