#include "general.hpp"
#include "objs.hpp"

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

template <typename V>
Rect2::Rect2(V pos1, V size1) {
    pos = pos1;
    size = size1;
}

float Rect2::getArea() {
    return size.x * size.y;
}