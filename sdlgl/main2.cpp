#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

int main(int argc, char *argv[]) {
    float scale = 1.25;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Triangle Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("font/neodgm.ttf", 32);
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, "Hello, SDL Mesh!", {255, 255, 255});
    SDL_Texture *texturetext = SDL_CreateTextureFromSurface(renderer, textSurface);

    int width, height;
    SDL_QueryTexture(texturetext, NULL, NULL, &width, &height);
    SDL_Rect renderRect = {0, 0, width, height};
    renderRect = {24, 24, width, height};
    
    SDL_Vertex vertices[3] = {
        {{400, 300}, {255, 0, 0, 255}, {0, 0}}, // Red vertex
        {{800, 300}, {0, 255, 0, 255}, {0, 0}},  // Green vertex
        {{800, 0}, {0, 0, 255, 255}, {0, 0}}  // Blue vertex
    };
    int indices[3] = {0, 1, 2};

    int running = 1;
    while (running) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texturetext, NULL, &renderRect);
        SDL_RenderGeometry(renderer, NULL, vertices, 3, indices, 3);
        SDL_RenderPresent(renderer);
 
        //std::cout << SDL_GetError() << std::endl;
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }
    return 0;
}
