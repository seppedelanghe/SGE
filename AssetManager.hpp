#pragma once

#include <map>
#include <string>
#include "TextureManager.hpp"
#include "ECS/Vector2.hpp"
#include "ECS/ECS.hpp"

class AssetManager
{
    public:
        AssetManager(Manager* man);
        ~AssetManager();

        void AddTexture(std::string id, const char* path);
        
        SDL_Texture* GetTexture(std::string id);


    private:
        Manager* manager;
        std::map<std::string, SDL_Texture*> textures;
};