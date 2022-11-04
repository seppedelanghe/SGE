#pragma once

#include <string>

class Map
{
    public:
        Map(std::string tId, int mscl, int tsize);
        ~Map();

        void LoadMap(std::string path, int w, int h);
		void AddTile(int srcX, int srcY, int xpos, int ypos);

    private:
        std::string texId;
        int mapScale;
        int tileSize;
        int scaledSize;
};