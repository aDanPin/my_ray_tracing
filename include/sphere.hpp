#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <math.h>
#include <limits>

#include "vector.hpp"

class Sphere {
    public:
    Vec3 center;
    double radius;

    Sphere(const Vec3 &c, const double &r) : center(c), radius(r) {}

    bool collision(const Vec3& first, const Vec3& second) {
        // сократить расстояние вектора до приемлемых значений (не надо)
        double a = (second.x - first.x) * (second.x - first.x) +
                   (second.y - first.y) * (second.y - first.y) +
                   (second.z - first.z) * (second.z - first.z);
        double b = -2*((first.x - center.x) * (second.x - first.x) +
                       (first.y - center.y) * (second.y - first.y) +
                       (first.z - center.z) * (second.z - first.z));
        double c = (first.x - center.x) * (first.x - center.x) +
                   (first.y - center.y) * (first.y - center.y) +
                   (first.z - center.z) * (first.z - center.z) -
                   radius * radius;

        double D = b*b - 4*a*c;

        if (D >= 0)
            return true;
        else
            return false;
    }
};

#endif // SPHERE_HPP
