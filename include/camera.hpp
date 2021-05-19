#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vector.hpp"

class Camera{
    public:
    int width, height;
    Vec3f position, direction;
    float distance;

    Camera(int w, int h, Vec3f p, Vec3f d, float dis):
        width(w), height(h), position(p), direction(d), distance(dis) {}
};

#endif // CAMERA_HPP
