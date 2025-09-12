#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

int main() {
    float scale = 1.25;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Triangle Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *sdlTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 600);
    SDL_SetRenderTarget(renderer, sdlTexture);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 600, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    std::cout << glGetString(GL_VERSION) << std::endl;

    int running = 1;
    while (running) {
        //SDL_SetRenderTarget(renderer, sdlTexture);
        SDL_Rect a = {0, 0, 40, 40};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &a);
        SDL_RenderPresent(renderer);
        /*
        SDL_RenderFlush(renderer);
        SDL_GL_BindTexture(sdlTexture, NULL, NULL);

        glDisable(GL_TEXTURE_2D);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(400.0f, 300.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(800.0f, 300.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(800.0f, 600.0f);
        glEnd();

        glEnable(GL_TEXTURE_2D);
        SDL_GL_BindTexture(sdlTexture, NULL, NULL);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 600.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(800.0f, 600.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(800.0f, 0.0f); 
        glEnd();
        glFlush();

        //std::cout << SDL_GetError() << std::endl;
        */
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }
    return 0;
}
