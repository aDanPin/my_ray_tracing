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
    std::vector<LightSphere> lSpheres;

    public:
    Camera camera;
    std::string path;

    Scene(const Camera &c, const std::string& p): camera(c), path(p){
        framebuffer = std::vector<Vec3>(camera.width * camera.height);

        for (size_t j = 0; j < camera.height; j++) {
            for (size_t i = 0; i < camera.width; i++) {
//                framebuffer[i + j * camera.width] = Vec3(j/float(camera.height),
//                                                          i/float(camera.width),
//                                                          0);
                framebuffer[i + j * camera.width] = Vec3(0, 0, 0);
            }
        }
    }

    void add(const Sphere& S){
        spheres.push_back(S);
    }

    void add(const LightSphere& S){
        lSpheres.push_back(S);
    }

    void render() {
        for (size_t j = 0; j < camera.height; j++) {
            for (size_t i = 0; i < camera.width; i++) {
                double z = ((camera.height + 0.5) / 2.) - (double)j;
                double x = ((-camera.width + 0.5) / 2.) + (double)i;

                Vec3 dir = Vec3(x, camera.distance, z);

                framebuffer[i+j*camera.width] = cast_ray(camera.position, dir, 0);

//                if (sp.collision(camera.position, dir)){
//                    framebuffer[i+j*camera.width] = {0,0, 200};
//                }
            }
        }
    }

    const int RECURSION_DEPTH = 256;
    const double ABSORPTION_COEF = 0.02;

    Vec3 cast_ray(const Vec3& src, const Vec3& dir, int r_depth = 0) {
        if (  r_depth >= RECURSION_DEPTH){
            return Vec3(256., 256.,256.) * std::pow( 1-ABSORPTION_COEF, r_depth );
        }
        else{
            // find
            double lRange = std::numeric_limits<double>::max();
            LightSphere* nearL;
            for (auto light : lSpheres) {
                Vec3 collision;
                bool have_collision;
                std::tie(have_collision, collision) = light.collision(src, dir);

                if(have_collision){
                    bool r = Vec3::range(src, collision);
                    if (r < lRange){
                        lRange = r;
                        nearL= &light;
                    }
                }
            }

            double range = std::numeric_limits<double>::max();
            Sphere* near;
            for (auto sphere : spheres) {
                Vec3 collision;
                bool have_collision;
                std::tie(have_collision, collision) = sphere.collision(src, dir);

                if(have_collision){
                    bool r = Vec3::range(src, collision);
                    if (r < range){
                        range = r;
                        near = &sphere;
                    }
                }
            }

            if (lRange < range){
                // Вернуть вектор
            } else {
                // Найти отреженный луч и продолжить поиск
                Vec3 reflection = nearL->reflection(src, dir);
            }


            near =  nullptr;
            nearL = nullptr;
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
