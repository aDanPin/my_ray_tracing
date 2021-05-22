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
    std::vector<Vec3> framebuffer;
    std::vector<Sphere> spheres;

    public:
    Camera camera;
    std::string path;

    Scene(const Camera &c, const std::string& p): camera(c), path(p){
        framebuffer = std::vector<Vec3>(camera.width * camera.height);

        for (size_t j = 0; j < camera.height; j++) {
            for (size_t i = 0; i < camera.width; i++) {
                framebuffer[i + j * camera.width] = Vec3(j/float(camera.height),
                                                          i/float(camera.width),
                                                          0);
            }
        }

    }

    void add(const Sphere& S){
        spheres.push_back(S);
    }

    void render() {
        for (size_t j = 0; j < camera.height; j++) {
            for (size_t i = 0; i < camera.width; i++) {
                for(auto sp : spheres){
                    double z = ((camera.height + 0.5) / 2.) - (double)j;
                    double x = ((-camera.width + 0.5) / 2.) + (double)i;

                    Vec3 dir = Vec3(x, camera.distance, z);

                    //framebuffer[i+j*camera.width] = cast_ray(camera.position, dir, sp);

                    if (sp.collision(camera.position, dir)){
                        framebuffer[i+j*camera.width] = {0, 0, 200};
                    }
                }
            }
        }
    }


    void write() {
        std::ofstream ofs; // save the framebuffer to file
        ofs.open(path);
        ofs << "P6\n" << camera.width << " " << camera.height << "\n255\n";
        for (size_t i = 0; i < camera.height * camera.width; ++i) {
            ofs << (char)(255 * std::max(0., std::min(1., framebuffer[i].x)))
                << (char)(255 * std::max(0., std::min(1., framebuffer[i].y)))
                << (char)(255 * std::max(0., std::min(1., framebuffer[i].z)));
        }
        ofs.close();
    }
};

#endif // SCENE_HPP
