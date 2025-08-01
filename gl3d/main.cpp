#include "script/general.hpp"
#include "script/objs.hpp"

int main(int argc, char *argv[]) {
    Cuboid3 c = Cuboid3(Vec3(), Vec3(), Vec3());
    std::cout << c.pos.x << std::endl;
    Game game = Game();
    glfwDestroyWindow(game.window);
    glfwTerminate();
    return 0;
}
