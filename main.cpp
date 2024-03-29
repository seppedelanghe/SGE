#include "Game.hpp"
#include "Utils/noise.hpp"

Game *game = nullptr;

int main(int argc, const char * argv[]) {

    try {
        const int FPS = 60;
        const int FRAME_DELAY = 1000 / FPS;

        Uint32 frameStart;
        int frameTime;

        game = new Game();
        game->init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, false);

        while (game->running()) {

            frameStart = SDL_GetTicks(); // time since SDL init

            game->handleEvents();
            game->update();
            game->render();

            frameTime = SDL_GetTicks() - frameStart; // Time taken to handle, update and render

            if (FRAME_DELAY > frameTime)
                SDL_Delay(FRAME_DELAY - frameTime); // wait => cap FPS

        }

        game->clean();

    } catch(const char* msg) {
        std::cerr << "Error: " << msg << std::endl;
        return 1;
    }

    return 0;
}
