#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>
#include <limits>
#include <tuple>

#include "solid.hpp"
#include "vector.hpp"

double DELTA = 0.1;

class Sphere : Solid {
    public:
    Vec3 center;
    double radius;

    Sphere(const Vec3 &c = Vec3(), const double &r = 0.) : center(c), radius(r) {}

    Vec3 reflection(const Vec3& src, const Vec3& dst, const Vec3& collision) {
        Vec3 V = dst - src;
        Vec3 N = collision - center;
        Vec3 R = -2 * (V* N) ^ N + V;

        std::cout << "Reflection: from"  << collision << "to: "<< R<< std::endl;

        return R;
    }

    virtual std::tuple<bool, Vec3> collision(const Vec3& src, const Vec3& dir) const {
        // сократить расстояние вектора до приемлемых значений (не надо)
/*
        Vec3 s = center - src;
        Vec3 d = dir - src;

        // d - единичный вектор?
        Vec3 a = d * d;
        Vec3 b = -2*(d^s);
        Vec3 c = s*s - radius*radius;

//        Vec3 D = 4( (d^s)*(d^s) - d*d*(s*s - radius*radius));
        double D = b*b - 4*a*c;

        std::cout<< "D: " << D<<std::endl;
        if (D >= 0) {
            double t = (-a - std::sqrt(D))/ 4*a*c;

            Vec3 collision = src + d*t;
            return std::tuple<double, Vec3>(std::move(true), std::move(collision));
        }
        else{
            return std::tuple<double, Vec3>(std::move(false),std::move( Vec3()));
        }
*/

        double a = (dir.x - src.x) * (dir.x - src.x) +
                   (dir.y - src.y) * (dir.y - src.y) +
                   (dir.z - src.z) * (dir.z - src.z);
        double b = -2*((src.x - center.x) * (dir.x - src.x) +
                       (src.y - center.y) * (dir.y - src.y) +
                       (src.z - center.z) * (dir.z - src.z));
        double c = (src.x - center.x) * (src.x - center.x) +
                   (src.y - center.y) * (src.y - center.y) +
                   (src.z - center.z) * (src.z - center.z) -
                   radius * radius;

        double D = b*b - 4*a*c;

        double t = (-b + std::sqrt(D))/(2*a);
        if (D >= 0){
            Vec3 collision(
                -(src.x + (dir.x - src.x)*t),
                -(src.y + (dir.y - src.y)*t),
                -(src.z + (dir.z - src.z)*t)
            );

            // collision = collision + (collision - center) * DELTA / Vec3::range(collision, center);
            return std::tuple<double, Vec3>(std::move(true), std::move(collision));
        }
        else{
            return std::tuple<double, Vec3>(std::move(false),std::move( Vec3()));
        }
    }

};

class LightSphere : public Sphere{
    public:
    LightSphere(const Vec3 &c, const double &r) : Sphere(c, r){
    }
};

#endif // SPHERE_HPP
