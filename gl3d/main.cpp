#include "script/general.hpp"
#include "script/objs.hpp"

int main(int argc, char *argv[]) {
    Cuboid3 c = Cuboid3(Vec3(), Vec3(), Vec3());
    ColorCuboid3 cc = ColorCuboid3(Vec3(), Vec3(), Vec3(), {0.0, 1.0, 0.0, 1.0});
    std::cout << cc.color[1] << std::endl;
    Game game = Game();
    glfwDestroyWindow(game.window);
    glfwTerminate();
    return 0;
}
