#include "Game.hpp"

#include "ECS/Vector2.hpp"
#include "ECS/Collision.hpp"

#include "ECS/C/Components.hpp"
#include "ECS/A/Map.hpp"
#include "ECS/A/TextureManager.hpp"
#include "ECS/A/AssetManager.hpp"

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

    assets->AddTexture("tileset", "assets/pack.png");
    assets->AddTexture("player", "assets/human1.png");
    assets->AddTexture("box", "assets/cut/dirt.png");

    map = new Map("tileset", 2, 16);
    map->LoadMap(MAPFILE, 40, 40);

    try
    {
        player.addComponent<TransformComponent>(400, 400, 16, 16, 4);

        player.addComponent<SpriteComponent>("player", 1, 200, 1);
        player.getComponent<SpriteComponent>().addAnimation("Left", 0, 3, 100);
        player.getComponent<SpriteComponent>().addAnimation("Down", 1, 3, 100);
        player.getComponent<SpriteComponent>().addAnimation("Up", 2, 3, 100);
        player.getComponent<SpriteComponent>().addAnimation("Right", 3, 3, 100);

        player.addComponent<KeyboardController>();
        player.addComponent<ColliderComponent>("player");
        
        player.addComponent<ScoreComponent>(); // Keep score
        player.addComponent<HealthComponent>(100, 75); // 100 max => 75 start
        
        player.addGroup(groupPlayers);



        box.addComponent<TransformComponent>(600, 400);
        box.addComponent<SpriteComponent>("box");
        box.addComponent<ColliderComponent>("box");
        box.addComponent<PickupComponent>("pointsbox", 10);
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
            player.getComponent<TransformComponent>().position = pPos;
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
    for (auto& t : tiles)
    {
        t->draw();
    }

    for (auto& c : colliders)
    {
        c->draw();
    }

    for (auto& p : players)
    {
        p->draw();
    }

    for (auto& p : projectiles)
    {
        p->draw();
    }

    for (auto& c : collectables)
    {
        c->draw();
    }
 
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