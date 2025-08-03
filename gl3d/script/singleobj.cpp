#include "general.hpp"
#include "objs.hpp"

SingleObj::SingleObj() {

}

ColorCuboid3::ColorCuboid3(std::shared_ptr<Vec3> pos, std::shared_ptr<Vec3> size, std::shared_ptr<Vec3> rot, std::array<float, 4> color) {
    this->pos = pos;
    this->size = size;
    this->rot = rot;
    this->color = color;
}