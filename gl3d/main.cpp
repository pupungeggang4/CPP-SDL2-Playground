#include "script/general.hpp"
#include "script/objs.hpp"

int main(int argc, char *argv[]) {
    Cuboid3 c = Cuboid3(std::make_shared<Vec3>(0.0, 0.0, 0.0), std::make_shared<Vec3>(1.0, 1.0, 1.0), std::make_shared<Vec3>(0.0, 0.0, 0.0));
    Game game = Game();
    glfwDestroyWindow(game.window);
    glfwTerminate();
    return 0;
}
