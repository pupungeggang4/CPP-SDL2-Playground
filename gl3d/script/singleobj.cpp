#include "general.hpp"
#include "objs.hpp"

SingleObj::SingleObj() {

}

ColorCuboid3::ColorCuboid3(Vec3 pos, Vec3 size, Vec3 rot, std::array<float, 4> color) {
    this->pos = pos;
    this->size = size;
    this->rot = rot;
    this->color = color;
}