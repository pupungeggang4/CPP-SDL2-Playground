#include "general.hpp"
#include "bufferdata.hpp"

class Game;
class Cuboid3;
class Vec3;
class Part3;
class SingleObj;
class ColorCuboid3;

class Game {
    public:
        int success; float scale;
        char infoLog[2048];
        GLuint program, vShader, fShader;
        GLuint vao, bTriangle;
        GLint laPosition;
        GLFWwindow *window;

        Game();
        void gameGLInit();
        void gameSDLInit();
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
        Vec3 pos = Vec3(), size = Vec3(), rot = Vec3();
        Cuboid3(Vec3 pos, Vec3 size, Vec3 rot);
};

class Part3 {
    public:
        Shape3 shape;
};

class SingleObj {
    public:
        SingleObj();
};

class ColorCuboid3 {
    public:
        Vec3 pos = Vec3(), size = Vec3(), rot = Vec3();
        std::array<float, 4> color;
        ColorCuboid3(Vec3 pos, Vec3 size, Vec3 rot, std::array<float, 4> color);
};
