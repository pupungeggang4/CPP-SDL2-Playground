#include "general.hpp"
#include "objs.hpp"

Vec3::Vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Cuboid3::Cuboid3(Vec3 pos, Vec3 size, Vec3 rot) {
    this->pos = pos;
    this->size = size;
    this->rot = rot;
}