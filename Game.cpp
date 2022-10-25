#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "ECS/Vector2.hpp"
#include "ECS/Collision.hpp"

const char* MAPFILE = "assets/map32x16.txt";
const char* TILESETFILE = "assets/tileset.png";

Map* map = nullptr;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;


bool Game::isRunning = false;

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};


auto& player(manager.addEntity());
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));


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

    map = new Map();

    Map::LoadMap(MAPFILE, 32, 16);

    try
    {
        player.addComponent<TransformComponent>(320, 320, 24, 24, 4);
        player.addComponent<SpriteComponent>("assets/animation.png", 2, 200);
        player.getComponent<SpriteComponent>().addAnimation("Walk", 1, 4, 100);

        player.addComponent<KeyboardController>();
        player.addComponent<ColliderComponent>("player");
        player.addGroup(groupPlayers);
    }
    catch(const char* msg)
    {
        std::cerr << "Error: " << msg << std::endl;
    }
}

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
    manager.refresh();
    manager.update();

    Vector2 pVel = player.getComponent<TransformComponent>().velocity;
    int pSpeed = player.getComponent<TransformComponent>().speed;

    for (auto t : tiles)
    {
        t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
        t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
    }
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
    
    for (auto& p : players)
    {
        p->draw();
    }

    for (auto& e : enemies)
    {
        e->draw();
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



void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, TILESETFILE);
    tile.addGroup(groupMap);
}