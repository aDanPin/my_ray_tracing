#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "vector.hpp"

class Scene{
    public:
    size_t width;
    size_t height;
    std::string path;

    std::vector<Vec3f> framebuffer;

    Scene(size_t w, size_t h,
          std::string& p): width(w), height(h), path(p){

        framebuffer = std::vector<Vec3f>(width*height);

        for (size_t j = 0; j<height; j++) {
            for (size_t i = 0; i<width; i++) {
                framebuffer[i+j*width] = Vec3f(j/float(height),i/float(width), 0);
            }
        }

    }

    void write() {
        std::ofstream ofs; // save the framebuffer to file
        ofs.open(path);
        ofs << "P6\n" << width << " " << height << "\n255\n";
        for (size_t i = 0; i < height*width; ++i) {
            for (size_t j = 0; j<3; j++) {
                ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
            }
        }
        ofs.close();
    }
};

#endif // SCENE_HPP
