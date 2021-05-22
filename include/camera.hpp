#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vector.hpp"

class Camera{
    public:
    int width, height;
    Vec3 position, direction;
    float distance;

    Camera(int w, int h, Vec3 p, Vec3 d, float dis):
        width(w), height(h), position(p), direction(d), distance(dis) {}
};

#endif // CAMERA_HPP
