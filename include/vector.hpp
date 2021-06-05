#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

class Vec3 {
    public:
    double x, y, z;

    Vec3(double X =0, double Y = 0, double Z = 0): x(X), y(Y), z(Z){}

    static double range(const Vec3& first, const Vec3& second){
        return sqrt((second.x - first.x) * (second.x - first.x) +
                    (second.y - first.y) * (second.y - first.y) +
                    (second.z - first.z) * (second.z - first.z));
    }

    static double range(const Vec3& first){
        return Vec3::range(Vec3(), first);
    }


};

Vec3& operator+=( Vec3& left, const Vec3& right) {
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;
    return left;
}

Vec3& operator-=( Vec3& left, const Vec3& right) {
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;
    return left;
}

const Vec3 operator+(const Vec3& left) {
    return Vec3(left);
}

const Vec3 operator-(const Vec3& left) {
    return  Vec3(-left.x, -left.y, -left.z);
}

const Vec3 operator+(const Vec3& left, const Vec3& right) {
    return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
}

const Vec3 operator-(const Vec3& left, const Vec3& right) {
    return Vec3(left.x - right.x, left.y - right.y, left.z - right.z);
}


const Vec3 operator-(const Vec3& left, const double m) {
    return Vec3(left.x - m, left.y - m, left.z - m);
}

// Скалярное произведение
const double operator *(const Vec3& left, const Vec3& right) {
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

// Векторное произведение
const Vec3 operator ^(const Vec3& left, const Vec3& right) {
    return  -Vec3(left.y * right.z - left.z * right.y,
                  left.z * right.x - left.x * right.z,
                  left.x * right.y - left.y * right.x);
}

// Векторное произведение
double dot(const Vec3& first, const Vec3& second) {
    return (first * second) / Vec3::range(second);
}


// Произведение на костанту
const Vec3 operator *(const Vec3& left, const double& c) {
    return Vec3(left.x * c, left.y * c, left.z * c);
}

// Деление на костанту
const Vec3 operator /(const Vec3& left, const double& c) {
    double f = 1./c;
    return Vec3(left.x * f, left.y * f, left.z * f);
}

bool operator !=(const Vec3& left, const Vec3& right) {
    return left.x != right.x ||
           left.y != right.y ||
           left.z != right.z;
}


std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    out << v.x << " " << v.y <<" "<< v.z << " ";
    return out;
}

static Vec3 approx(const Vec3& first, const Vec3& second) {
    Vec3 t = (second - first)/ sqrt((second.x - first.x) * (second.x - first.x) +
                                        (second.y - first.y) * (second.y - first.y) +
                                        (second.z - first.z) * (second.z - first.z));
    return second + t;
}

static Vec3 approx(const Vec3& first, const double scale_to) {
    return first * scale_to / Vec3::range(Vec3(), first);
}


void Vec3test() {
    Vec3 first ( 8, 8, 8);
    Vec3 second ( 16, 8, 4);

    std::cout<< first << ' ' << second << std::endl;
    std::cout<< "Test +" << std::endl;
    std::cout<< "Should be: "<< 24 << ", "<< 16<< ", "<< 12 << std::endl;
    std::cout<< "Ans:       " << first + second << std::endl;

    std::cout<< "Test -" << std::endl;
    std::cout<< "Should be: "<< 8 << ", "<< 0<< ", "<< -4 << std::endl;
    std::cout<< "Ans:       " << second - first << std::endl;

    std::cout<< "Test *" << std::endl;
    std::cout<< "Should be: "<< 224 << std::endl;
    std::cout<< "Ans:       " << second * first << std::endl;

    std::cout<< "Test ^" << std::endl;
    std::cout<< "Should be: "<< -32 << ", "<< 96<<", "<< -64 << std::endl;
    std::cout<< "Ans:       " << (second ^ first) << std::endl;

    std::cout<< "Test *const" << std::endl;
    std::cout<< "Should be: "<< -32 << ", "<< -16<<", "<< -8 << std::endl;
    std::cout<< "Ans:       " << second * (-2) << std::endl;

    std::cout<< "Test /const" << std::endl;
    std::cout<< "Should be: "<< -8 << ", "<< -4<<", "<< -2 << std::endl;
    std::cout<< "Ans:       " << second / (-2) << std::endl;

}


#endif // VECTOR_HPP
