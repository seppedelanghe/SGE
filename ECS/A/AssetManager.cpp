#include "AssetManager.hpp"
#include "../C/Components.hpp"

AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

// Game objects
void AssetManager::CreateProjectile(Vector2 pos, int range, int speed, Vector2 vel, std::string tId)
{
    auto& projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    projectile.addComponent<SpriteComponent>(tId);
    projectile.addComponent<ProjectileComponent>(range, speed, vel);
    projectile.addComponent<ColliderComponent>("projectile");

    projectile.addGroup(Game::groupProjectiles);
}


// Textures
void AssetManager::AddTexture(std::string id, const char* path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
    return textures[id];
}


// Fonts
void AssetManager::AddFont(std::string id, const char* path, int fontSize)
{
    fonts.emplace(id, TTF_OpenFont(path, fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id)
{
    return fonts[id];
}