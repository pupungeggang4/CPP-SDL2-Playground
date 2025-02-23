#include "general.hpp"
#include "var.hpp"

const char *vSource = R"(
    
)";

const char *fSource = R"(

)";

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Init fail" << std::endl;
    }

    window = SDL_CreateWindow("Player Movement Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);

    gladLoadGLES2Loader((GLADloadproc) SDL_GL_GetProcAddress);

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    return 0;
}
