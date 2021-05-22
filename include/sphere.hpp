#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <math.h>
#include <limits>

#include "vector.hpp"

class Sphere {
    public:
    Vec3 center;
    float radius;

    Sphere(const Vec3 &c, const float &r) : center(c), radius(r) {}

//    bool ray_intersect(const Vec3 &orig, const Vec3 &dir, float &t0) const {
//        Vec3 L = center - orig;
//        float tca = L*dir;
//        float d2 = L*L - tca*tca;
//        if (d2 > radius*radius) return false;
//        float thc = sqrtf(radius*radius - d2);
//        t0       = tca - thc;
//        float t1 = tca + thc;
//        if (t0 < 0) t0 = t1;
//        if (t0 < 0) return false;
//        return true;
//    }

    bool collision(const Vec3& first, const Vec3& second) {
        float a = (second.x - first.x) * (second.x - first.x) +
                  (second.y - first.y) * (second.y - first.y) +
                  (second.z - first.z) * (second.z - first.z);
        float b = -2*((first.x - center.x) * (second.x - first.x) +
                      (first.y - center.y) * (second.y - first.y) +
                      (first.z - center.z) * (second.z - first.z));
        float c = (first.x - center.x) * (first.x - center.x) +
                  (first.y - center.y) * (first.y - center.y) +
                  (first.z - center.z) * (first.z - center.z) -
                  radius * radius;

        float D = b*b - 4*a*c;

        if (D < 0)
            return false;

        return true;
    }
};

#endif // SPHERE_HPP
