#include "script/general.hpp"
#include "script/objs.hpp"

int main(int argc, char *argv[]) {
    Game game = Game();
    std::shared_ptr<Rect2> r1 = std::make_shared<Rect2>(
        std::make_shared<Vec2>(0.0, 0.0),
        std::make_shared<Vec2>(3.5, 3.5)
    );
    std::cout << r1->getArea() << std::endl;
    return 0;
}