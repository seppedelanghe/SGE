#pragma once

#include <map>
#include <string>
#include "TextureManager.hpp"
#include "IS/Physics/Vector2.hpp"
#include "ECS/ECS.hpp"
#include "SDL_ttf.h"

class AssetManager
{
    public:
        AssetManager(Manager* man);
        ~AssetManager();


        // Game objects
        void CreateProjectile(Vector2 pos, int range, int speed, Vector2 vel, std::string tId);

        // Textures
        void AddTexture(std::string id, const char* path);        
        SDL_Texture* GetTexture(std::string id);

        // Fonts
        void AddFont(std::string id, const char* path, int fontSize);
        TTF_Font* GetFont(std::string id);

    private:
        Manager* manager;
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;

};
