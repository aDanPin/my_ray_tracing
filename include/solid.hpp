#ifndef SOLID_HPP
#define SOLID_HPP

#include "vector.hpp"

class Solid{
    virtual Vec3 reflection(const Vec3& stc, const Vec3& dir, const Vec3& collPoint){}
    virtual std::tuple<bool, Vec3> collision(const Vec3& first, const Vec3& second){}
};

#endif // SOLID_HPP
