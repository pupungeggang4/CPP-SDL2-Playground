#include "objs.hpp"

Game::Game() {
    gameSDLInit();
    run();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::gameSDLInit() {
    SDL_Init(SDL_INIT_VIDEO);

    #if SCALED == 1
    window = SDL_CreateWindow("2D Adventure Game", 0, 0, 1280 * 1.5, 720 * 1.5, SDL_WINDOW_SHOWN);
    scale = 1.5;
    #else
    window = SDL_CreateWindow("2D Adventure Game", 0, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    scale = 1;
    #endif
    screenRect = new SDL_Rect({0, 0, int(1280 * scale), int(720 * scale)});
    surface = SDL_GetWindowSurface(window);
    surfaceUI = SDL_CreateRGBSurface(0, 1280, 720, 32, 0, 0, 0, 0);
}

void Game::run() {
    SDL_Event e;
    while (running) {
        SDL_Rect a = {0, 0, 640, 720};
        SDL_FillRect(surfaceUI, NULL, 0x00000000);
        SDL_FillRect(surface, NULL, 0xFFFFFFFF);
        SDL_FillRect(surfaceUI, &a, 0xFFFF00FF);
        SDL_BlitScaled(surfaceUI, NULL, surface, screenRect);
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