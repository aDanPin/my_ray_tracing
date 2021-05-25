#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>
#include <limits>
#include <tuple>

#include "solid.hpp"
#include "vector.hpp"

class Sphere : Solid {
    public:
    Vec3 center;
    double radius;

    Sphere(const Vec3 &c = Vec3(), const double &r = 0.) : center(c), radius(r) {}

    Vec3 reflection(const Vec3& src, const Vec3& dst, const Vec3& collision) {
        Vec3 V = dst - src;
        Vec3 N = collision - center;
        Vec3 R = -2 * (V* N) ^ N + V;
        return R;
    }

    virtual std::tuple<bool, Vec3> collision(const Vec3& first, const Vec3& second) {
        // сократить расстояние вектора до приемлемых значений (не надо)

        Vec3 d = second - first;
        Vec3 s = radius - first;

        double a = d*d;
        double b = -2*(d*s);
        double c = s*s - radius*radius;

        double D =  b*b - 4*a*c;

            double t = (-b + std::sqrt(D))/(2*a);

            std::cout<< "first: "<< first<<std::endl;
            std::cout<< "second: "<< second<<std::endl;

            std::cout<< "radius: "<< radius<<std::endl;
            std::cout<< "center: "<< center<<std::endl;

            std::cout<< "b: "<< b<<std::endl;
            std::cout<< "D: "<< D<<std::endl;
            std::cout<< "sqrt D: "<< std::sqrt(D)<<std::endl;
            std::cout<< "a: "<< a<<std::endl;
            std::cout<< "T: "<< t<<std::endl;

        if (D > 0){
            Vec3 collision(
                first.x + (second.x - first.x)*t,
                first.y + (second.y - first.y)*t,
                first.z + (second.z - first.z)*t
            );
            return std::tuple<double, Vec3>(true, collision);
        }
        else{
            return std::tuple<double, Vec3>(false, Vec3());
        }
    }
};

class LightSphere : public Sphere{
    public:
    LightSphere(const Vec3 &c, const double &r){
        Sphere(c, r);
    }
};

#endif // SPHERE_HPP
