#include "general.hpp"

class Vector3;
class Cuboid3;
class ColorCuboid3;
class Part3;

class Game;

class Game {
    public:
        GLuint program, vShader, fShader;
        GLuint vao, bTriangle;
        GLint laPosition;

        void gameGLInit();
        void gameSDLInit();
};

class Vector3 {
    public:
        float x, y, z;
        Vector3(float x = 0.0, float y = 0.0, float z = 0.0);
};

class Cuboid3 {
    public:
        Vector3 pos = Vector3(), size = Vector3(), rot = Vector3();
        Cuboid3(Vector3 pos, Vector3 size, Vector3 rot);
};

class Part3 {

};

class ColorCuboid3 {

};
