#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "vector.hpp"
#include "camera.hpp"
#include "sphere.hpp"

class Scene{
    private:
    std::vector<Vec3f> framebuffer;
    std::vector<Sphere> spheres;

    public:
    Camera camera;
    std::string path;


    Scene(const Camera &c, const std::string& p): camera(c), path(p){
        framebuffer = std::vector<Vec3f>(camera.width * camera.height);

        for (size_t j = 0; j < camera.height; j++) {
            for (size_t i = 0; i < camera.width; i++) {
                framebuffer[i + j * camera.width] = Vec3f(j/float(camera.height),
                                                          i/float(camera.width),
                                                          0);
            }
        }

    }

    void add(const Sphere& S){
        spheres.push_back(S);
    }

    void render() {

    }

    void write() {
        std::ofstream ofs; // save the framebuffer to file
        ofs.open(path);
        ofs << "P6\n" << camera.width << " " << camera.height << "\n255\n";
        for (size_t i = 0; i < camera.height * camera.width; ++i) {
            for (size_t j = 0; j < 3; j++) {
                ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
            }
        }
        ofs.close();
    }
};

#endif // SCENE_HPP
