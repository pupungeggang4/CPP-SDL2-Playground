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
        GLuint vao, bTriangle, bHUD, bCuboid, bCuboidIndex;
        GLint luModeV, luPPos, luPSize, luPRot, luMPos, luMSize, luMRot, luCPos, luCRot, luCProj, luModeF, luLightD, luColor, laPosition, laTexcoord, laNormal;
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
        std::shared_ptr<Vec3> pos, size, rot;
        Cuboid3(std::shared_ptr<Vec3> pos, std::shared_ptr<Vec3> size, std::shared_ptr<Vec3> rot);
};

class Part3 {
    public:
        std::shared_ptr<Shape3> shape;
};

class SingleObj {
    public:
        SingleObj();
};

class ColorCuboid3 {
    public:
        std::shared_ptr<Vec3> pos, size, rot;
        std::array<float, 4> color;
        ColorCuboid3(std::shared_ptr<Vec3> pos, std::shared_ptr<Vec3> size, std::shared_ptr<Vec3> rot, std::array<float, 4> color);
};
