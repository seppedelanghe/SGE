#pragma once

#include <string>

class Map
{
    public:
        Map(std::string tId, int mscl, int tsize);
        Map(std::string tId, int mscl, int tsize, bool hasCollisionMap);
        ~Map();

        void LoadMap(std::string path, int w, int h);
		void AddTile(int srcX, int srcY, int xpos, int ypos);

    private:
        std::string texId;
        bool hasCollision;
        int mapScale;
        int tileSize;
        int scaledSize;
};