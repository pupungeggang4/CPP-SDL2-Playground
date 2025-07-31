#include "general.hpp"

class Game;
class Vec2;
class Rect2;

class Game {
    public:
        Game();
        void gameSDLInit();
        void run();
        void loop();
};

class Vec2 {
    public:
        float x, y;
        Vec2(float x = 0, float y = 0);
};

class Rect2 {
    public:
        Vec2 pos, size;
        Rect2(Vec2 pos, Vec2 size);
};