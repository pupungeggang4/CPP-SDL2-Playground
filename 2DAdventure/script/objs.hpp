#pragma once
#include "general.hpp"

class Game {
    public:
        //Player player = Player(); World world = World();
        SDL_Window *window;
        Game();
        void gameSDLInit();
        void run();
        void loop();
};

class Player {
    public:
        Player();
};

class World {
    public:
        //WorldPlayer player = WorldPlayer();
        World();
};

class WorldPlayer {
    public:
        float speed = 200.0;
        //Vec2 pos;
        WorldPlayer();
};

class Vec2 {
    public:
        float x, y;
        Vec2(float x = 0, float y = 0);
};

template <typename V>
class Rect2 {
    public:
        V pos = Vec2();
        V size = Vec2();
        Rect2(V pos1, V size1);
        float getArea();
};