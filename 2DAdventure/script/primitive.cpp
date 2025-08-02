#include "general.hpp"
#include "objs.hpp"

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

bool Vec2::insideRect(std::shared_ptr<Rect2> r) {
    return this->x > r->pos->x - r->size->x / 2 && this->x < r->pos->x + r->size->x / 2 && this->y > r->pos->y - r->size->y / 2 && this->y < r->pos->y + r->size->y / 2;
}

Rect2::Rect2(std::shared_ptr<Vec2> pos, std::shared_ptr<Vec2> size) {
    this->pos = pos;
    this->size = size;
}

float Rect2::getArea() {
    return this->size->x * this->size->y;
}