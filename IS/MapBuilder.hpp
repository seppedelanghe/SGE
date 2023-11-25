#pragma once

#include <string>
#include "../Game.hpp"

class MapBuilder
{
    public:
        MapBuilder(std::string texture_id, float scale, int tile_size);
        MapBuilder(std::string texture_id, float scale, int tile_size, bool has_collision_map);
        MapBuilder(std::string texture_id, float scale, int tile_size, bool has_collision_map, Game::groupLabels group);
        ~MapBuilder();

        void LoadMap(std::string path, int w, int h);
        void Fill(int texX, int texY, int w, int h, bool outerCollision);

        void AddTile(int srcX, int srcY, int xpos, int ypos, Game::groupLabels group);
        void AddCollisionTile(int x, int y);

    private:
        std::string textureId;
        bool hasCollision;
        float scaleFactor;
        int tileSize;
        int scaledSize;
        Game::groupLabels renderGroup;
};
