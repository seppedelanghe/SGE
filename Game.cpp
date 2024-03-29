#include <cstdio>
#include <ostream>
#include <sstream>

#include "Game.hpp"

#include "ECS/C/Components.hpp"
#include "ECS/A/TextureManager.hpp"
#include "ECS/A/AssetManager.hpp"

#include "IS/Physics/Vector2.hpp"
#include "IS/Physics/Collision.hpp"
#include "IS/MapBuilder.hpp"
#include "IS/Generators/MapGenerator.hpp"
#include "UI/UILabel.h"

const char* MAPFILE = "assets/map.txt";
const char* GROUNDFILE = "assets/ground.txt";

int* mapSize = new int[2] { 30, 20 };
MapBuilder* map = nullptr;
MapBuilder* ground = nullptr;
AStar astar = AStar(Heuristic::euclidiean);

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 960, 640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;
bool Game::isDebug = true;

auto& player(manager.addEntity());
auto& coin(manager.addEntity());
auto& tree(manager.addEntity());

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

    if (TTF_Init() == -1) {
        std::cout << "Error : Failed to init TTF" << std::endl;
    }

    Game::setup();
}


void Game::setup() 
{
    assets->AddFont("arial", "assets/arial.ttf", 16);

    assets->AddTexture("map", "assets/custom/world.png");
    assets->AddTexture("ground", "assets/custom/ground.png");
    assets->AddTexture("player", "assets/MiniWorldSprites/Characters/Champions/Arthax.png");
    assets->AddTexture("items", "assets/custom/items.png");

    map = new MapBuilder("map", 2.0f, 16, true);
    map->Fill(2, 0, mapSize[0] * 2, mapSize[1] * 2, true);
    // map->LoadMap(MAPFILE, 30, 20);

    // ground = new MapBuilder("ground", 2.0f, 16, true);
    // ground->LoadMap(GROUNDFILE, 30, 20);

    try
    {
        astar.UpdateSize(mapSize[0] * 16, mapSize[1] * 16);

        player.addComponent<TransformComponent>(16 * 10, 16 * 10, 16, 16, 1);

        int playerAnimSpeed = 100;
        player.addComponent<SpriteComponent>("player", 1, playerAnimSpeed, 0);

        player.getComponent<SpriteComponent>().addAnimation("Down", 0, 5, playerAnimSpeed);
        player.getComponent<SpriteComponent>().addAnimation("Up", 1, 5, playerAnimSpeed);
        player.getComponent<SpriteComponent>().addAnimation("Right", 2, 5, playerAnimSpeed);
        player.getComponent<SpriteComponent>().addAnimation("Left", 3, 5, playerAnimSpeed);

        player.getComponent<SpriteComponent>().addAnimation("DownIdle", 0, 1, playerAnimSpeed);
        player.getComponent<SpriteComponent>().addAnimation("UpIdle", 1, 1, playerAnimSpeed);
        player.getComponent<SpriteComponent>().addAnimation("RightIdle", 2, 1, playerAnimSpeed);
        player.getComponent<SpriteComponent>().addAnimation("LeftIdle", 3, 1, playerAnimSpeed);

        player.getComponent<SpriteComponent>().addAnimation("DownStrike", 4, 5, playerAnimSpeed);
        player.getComponent<SpriteComponent>().addAnimation("UpStrike", 5, 5, playerAnimSpeed);
        player.getComponent<SpriteComponent>().addAnimation("RightStrike", 6, 5, playerAnimSpeed);
        player.getComponent<SpriteComponent>().addAnimation("LeftStrike", 7, 5, playerAnimSpeed);

        player.addComponent<KeyboardController>();
        player.addComponent<PathFindingComponent>(&astar);
        player.getComponent<PathFindingComponent>().SetNormilizer(16);

        player.addComponent<MouseController>(&camera, true);
        player.addComponent<MouseSelectionComponent>(&camera);
        player.addComponent<ColliderComponent>("player");
        
        player.addComponent<ScoreComponent>("Coin");
        player.addComponent<HealthComponent>(100, 75); // 100 max => 75 start
        
        player.addGroup(groupPlayers);

        SDL_Color white = {250, 250, 250, 255};
        auto& healthLabel(manager.addEntity());
        healthLabel.addComponent<UILabel>(10, 10, "Health", "arial", white)
            .AssociateHealth(&player.getComponent<HealthComponent>());
        healthLabel.addGroup(Game::groupUI);

        auto& scoreLabel(manager.addEntity());
        scoreLabel.addComponent<UILabel>(10, 30, "Coin", "arial", white)
            .AssociateScore(&player.getComponent<ScoreComponent>());
        scoreLabel.addGroup(Game::groupUI);

        
        coin.addComponent<TransformComponent>(160, 200, 16, 16, 0.75f);
        coin.addComponent<SpriteComponent>("items", 1, 100, 0);
        coin.getComponent<SpriteComponent>().addAnimation("gold", 0, 1, 100);

        coin.addComponent<ColliderComponent>("coins");
        coin.addComponent<PickupComponent>("coins", 10);
        coin.addGroup(groupCollectables);


        tree.addComponent<TransformComponent>(120, 120, 16, 16, 2.0f);
        tree.addComponent<SpriteComponent>("ground");
        tree.getComponent<SpriteComponent>().setTexIndex(2, 0);
        tree.addComponent<ColliderComponent>("trees");

        SDL_Rect menuRect{ 0, 0, 100, 240 };
        tree.addComponent<MenuComponent>(menuRect);
        tree.getComponent<MenuComponent>().AddLabel("hello", 16, 16);

        tree.addComponent<MouseSelectionComponent>(&camera, 16, [](Entity& self) {
            Entity* e = &self;
            e->getComponent<MenuComponent>().Toggle();
        });
        

        tree.addGroup(groupColliders);

    }
    catch(const char* msg)
    {
        std::cerr << "Error: " << msg << std::endl;
    }

}


auto& tiles(manager.getGroup(Game::groupGround));
auto& buildings(manager.getGroup(Game::groupBuildings));
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
        astar.AddWall(Vector2(cCol.x / 16, cCol.y / 16));

        if (Collision::AABB(cCol, playerCol)) {
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
