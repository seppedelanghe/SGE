#pragma once

#include <string>

class Map
{
    public:
        Map(const char* mfp, int mscl, int tsize);
        ~Map();

		void AddTile(int srcX, int srcY, int xpos, int ypos);
        void LoadMap(std::string path, int w, int h);

    private:
        const char* mapFilePath;
        int mapScale;
        int tileSize;
        int scaledSize;
};