#pragma once

#include <map>
#include <string>
#include "TextureManager.hpp"
#include "../Vector2.hpp"
#include "../ECS.hpp"

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


    private:
        Manager* manager;
        std::map<std::string, SDL_Texture*> textures;
};