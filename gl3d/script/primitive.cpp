#include "general.hpp"
#include "objs.hpp"

Vec3::Vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Cuboid3::Cuboid3(std::shared_ptr<Vec3> pos, std::shared_ptr<Vec3> size, std::shared_ptr<Vec3> rot) {
    this->pos = pos;
    this->size = size;
    this->rot = rot;
}