#include "script/general.hpp"
#include "script/objs.hpp"

int main(int argc, char *argv[]) {
    Game game = Game();
    glfwDestroyWindow(game.window);
    glfwTerminate();
    return 0;
}
