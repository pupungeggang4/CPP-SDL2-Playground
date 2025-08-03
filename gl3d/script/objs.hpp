#include "general.hpp"
#include "bufferdata.hpp"

class Game;
class Cuboid3;
class Vec3;
class Part3;
class SingleObj;
class ColorCuboid3;
class Camera3;
class World;
using std::shared_ptr, std::make_shared;

class Game {
    public:
        int success; float scale;
        unsigned int fCurrent = 0, fPrevious = 0, delta = 0;
        char infoLog[2048];
        GLuint program, vShader, fShader;
        GLuint vao, bTriangle, bHUD, bCuboid, bCuboidIndex;
        GLint luModeV, luPPos, luPSize, luPRot, luMPos, luMSize, luMRot, luCPos, luCRot, luCProj, luModeF, luLightD, luColor, laPosition, laTexcoord, laNormal;
        GLFWwindow *window;

        shared_ptr<World> world; shared_ptr<Camera3> camera;
        shared_ptr<ColorCuboid3> c;

        Game();
        void gameGLInit();
        void gameSDLInit();
        void gameVarInit();
        void run();
        void loop();
        static void cbWindowSizeChange(GLFWwindow* window, int width, int height);
        static void cbKey(GLFWwindow* window, int key, int scancode, int action, int mods);
};

class Vec3 {
    public:
        float x, y, z;
        Vec3(float x = 0.0, float y = 0.0, float z = 0.0);
};

class Shape3 {
    public:
};

class Cuboid3 : public Shape3 {
    public:
        shared_ptr<Vec3> pos, size, rot;
        Cuboid3(shared_ptr<Vec3> pos, shared_ptr<Vec3> size, shared_ptr<Vec3> rot);
};

class Part3 {
    public:
        shared_ptr<Shape3> shape;
};

class SingleObj {
    public:
        SingleObj();
};

class ColorCuboid3 {
    public:
        shared_ptr<Vec3> pos, size, rot;
        std::array<float, 4> color;
        ColorCuboid3(shared_ptr<Vec3> pos, shared_ptr<Vec3> size, shared_ptr<Vec3> rot, std::array<float, 4> color);
        void render(Game *game, shared_ptr<Camera3> camera, shared_ptr<Vec3> lightD);
};

class Camera3 {
    public:
        shared_ptr<Vec3> pos, rot;
        float asp, fov, near, far;
        Camera3();
};

class World {
    public:
        shared_ptr<Vec3> lightD;
        World();
};