#include "script/general.hpp"
#include "script/objs.hpp"

int main(int argc, char *argv[]) {
    shared_ptr<Game> game = make_shared<Game>();
    glfwDestroyWindow(game->window);
    glfwTerminate();
    return 0;
}
