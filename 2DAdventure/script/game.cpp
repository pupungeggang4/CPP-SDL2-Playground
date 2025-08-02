#include "objs.hpp"

Game::Game() {
    gameSDLInit();
    run();
}

void Game::gameSDLInit() {
    SDL_Init(SDL_INIT_VIDEO);

    #ifdef __LINUX__
    window = SDL_CreateWindow("2D Adventure Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280 * 1.5, 720 * 1.5, SDL_WINDOW_SHOWN);
    #else
    window = SDL_CreateWindow("2D Adventure Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    #endif
    surface = SDL_GetWindowSurface(window);
}

void Game::run() {
    SDL_Event e;
    while (running) {
        SDL_FillRect(surface, NULL, 0xFFFFFFFF);
        SDL_UpdateWindowSurface(window);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
    }
}

void Game::loop() {

}