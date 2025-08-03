#include "general.hpp"
#include "objs.hpp"

Camera3::Camera3() {
    pos = make_shared<Vec3>(0.0, 0.0, -2.0);
    rot = make_shared<Vec3>(0.0, 0.0, 0.0);
    asp = 4.0 / 3.0; fov = 1.0; near = 0.1; far = 10.0;
}

World::World() {
    lightD = make_shared<Vec3>(0.0, 0.0, 1.0);
}