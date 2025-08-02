#include "objs.hpp"

Game::Game() {
    gameSDLInit();
    run();
}

void Game::gameSDLInit() {
    SDL_Init(SDL_INIT_VIDEO);
}

void Game::run() {

}

void Game::loop() {

}