#include "script/general.hpp"
#include "script/objs.hpp"

int main(int argc, char *argv[]) {
    Game game = Game();
    Rect2 r1 = Rect2(Vec2(0.0, 0.0), Vec2(2.5, 3.0));
    std::cout << r1.getArea() << std::endl;
    return 0;
}