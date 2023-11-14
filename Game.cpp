#include "Game.hpp"

#include "ECS/Vector2.hpp"
#include "ECS/Collision.hpp"

#include "ECS/C/Components.hpp"
#include "ECS/A/Map.hpp"
#include "ECS/A/TextureManager.hpp"
#include "ECS/A/AssetManager.hpp"
#include <sstream>

const char* MAPFILE = "assets/map.txt";

Map* map = nullptr;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 20 * 16, 640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& box(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) { // SDL Import success
        std::cout << "Subsystems Initialised..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            std::cout << "Renderer created!" << std::endl;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "Error : Failed to init TTF" << std::endl;
    }

    assets->AddFont("arial", "assets/arial.ttf", 16);

    assets->AddTexture("tileset", "assets/sheet-small.png");
    assets->AddTexture("player", "assets/humans.png");
    assets->AddTexture("cash", "assets/items/cash.png");

    map = new Map("tileset", 1, 64, true);
    map->LoadMap(MAPFILE, 12, 17);

    try
    {
        player.addComponent<TransformComponent>(16 * 10, 16 * 10, 128, 128, 0.5f);

        player.addComponent<SpriteComponent>("player", 1, 200, 0);
        player.getComponent<SpriteComponent>().addAnimation("Left", 1, 1, 100);
        player.getComponent<SpriteComponent>().addAnimation("Down", 2, 1, 100);
        player.getComponent<SpriteComponent>().addAnimation("Up", 3, 1, 100);
        player.getComponent<SpriteComponent>().addAnimation("Right", 4, 1, 100);

        player.addComponent<KeyboardController>();
        player.addComponent<ColliderComponent>("player");
        
        player.addComponent<ScoreComponent>("money"); // Keep track of money
        player.addComponent<HealthComponent>(100, 75); // 100 max => 75 start
        
        player.addGroup(groupPlayers);
        

        SDL_Color white = {255, 255, 255, 255};
        auto& healthLabel(manager.addEntity());
        healthLabel.addComponent<UILabel>(10, 10, "Health", "arial", white)
            .AssociateHealth(&player.getComponent<HealthComponent>());
        healthLabel.addGroup(Game::groupUI);

        auto& scoreLabel(manager.addEntity());
        scoreLabel.addComponent<UILabel>(10, 30, "Score", "arial", white)
            .AssociateScore(&player.getComponent<ScoreComponent>());
        scoreLabel.addGroup(Game::groupUI);

        
        box.addComponent<TransformComponent>(600, 400, 101, 106, 0.3f);
        box.addComponent<SpriteComponent>("cash");
        box.addComponent<ColliderComponent>("cash");
        box.addComponent<PickupComponent>("cash", 10);
        box.addGroup(groupCollectables);
    }
    catch(const char* msg)
    {
        std::cerr << "Error: " << msg << std::endl;
    }
}


auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& collectables(manager.getGroup(Game::groupCollectables));
auto& ui(manager.getGroup(Game::groupUI));

void Game::handleEvents()
{
    
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }
}

void Game::update()
{

    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2 pPos = player.getComponent<TransformComponent>().position;

    manager.refresh();
    manager.update();

    for (auto& c : colliders)
    {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol))
        {
            Vector2 colDir = *Collision::AABBDirection(cCol, playerCol);
            player.getComponent<TransformComponent>().position = pPos - colDir;
        }
    }

    for (auto& c : collectables)
    {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol))
        {
            c->getComponent<PickupComponent>().Take(player);
            c->destroy();
        }
    }

    for (auto& p : projectiles)
    {
        if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
        {
            p->destroy();
        }
    }

    camera.x = player.getComponent<TransformComponent>().position.x - camera.w / 2;
    camera.y = player.getComponent<TransformComponent>().position.y - camera.h / 2;

    if (camera.x < 0)
        camera.x = 0;

    if (camera.y < 0)
        camera.y = 0;

    if (camera.x > camera.w)
        camera.x = camera.w;
        
    if (camera.y > camera.h)
        camera.y = camera.h;
}



void Game::render()
{
    // Clear previous render
    SDL_RenderClear(renderer);
    
    // Add stuff to render
    manager.draw();

    // Present render
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Game cleaned..." << std::endl;
}
