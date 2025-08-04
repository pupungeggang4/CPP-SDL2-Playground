#pragma once
#include "general.hpp"

class Game;
class Player;
class World;
class WorldPlayer;
class Vec2;
class Rect2;

class Game {
    public:
        bool running = true;
        float scale;
        int delta, fDelta = 16;
        std::shared_ptr<Player> player = std::make_shared<Player>();
        std::shared_ptr<World> world = std::make_shared<World>();
        SDL_Window *window; SDL_Surface *surface, *surfaceUI; SDL_Renderer *renderer;
        SDL_Rect *screenRect;

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
        std::shared_ptr<WorldPlayer> player = std::make_shared<WorldPlayer>();
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
        bool insideRect(std::shared_ptr<Rect2> r);
};

class Rect2 {
    public:
        std::shared_ptr<Vec2> pos, size;
        Rect2(std::shared_ptr<Vec2> pos, std::shared_ptr<Vec2> size);
        float getArea();
};