#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <cmath>

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
        framebuffer = std::vector<Vec3>(camera.width * camera.height, Vec3());
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
                std::cout<< "1"<<std::endl;

                double z = ((camera.height + 0.5) / 2.) - (double)j;
                double x = ((-camera.width + 0.5) / 2.) + (double)i;

                Vec3 dir = Vec3(x, camera.distance, z);

                framebuffer[i+j*camera.width] = cast_ray(camera.position, dir);
            }
        }
    }

    const int RECURSION_DEPTH = 256;
    const double ABSORPTION_COEF = 0.5;

    Vec3 cast_ray(const Vec3& src, const Vec3& dir, int r_depth = 0) {
        std::cout<< "2"<<std::endl;
        if (  r_depth >= RECURSION_DEPTH){
            return Vec3(100., 100.,100.) * std::pow( ABSORPTION_COEF, r_depth );
        }
        else{
            // find
            bool got_l_collision = false;
            Vec3 lCollision;
            LightSphere* nearLSolid = NULL;
        std::cout<< "2.1"<<std::endl;

            std::tie(got_l_collision, lCollision, nearLSolid) =
                                                    find_neatest<LightSphere>(src, dir, lSpheres);

            if(got_l_collision){
                nearLSolid = NULL;
                return Vec3(256., 256., 256.) * std::pow(ABSORPTION_COEF, r_depth);
            }

            bool got_collision = false;
            Vec3 collision;
            Sphere* nearSolid = NULL;
        std::cout<< "2,2"<<std::endl;

            std::tie(got_collision, collision, nearSolid) = find_neatest<Sphere>(src, dir, spheres);
        std::cout<< "2,3"<<std::endl;

            if(got_collision){
                // продолжить рекурсию
                // найти новую точку отражения
        std::cout<< "2,4"<<std::endl;

                Vec3 reflected = nearSolid->reflection(src, dir, collision);
        std::cout<< "2,5"<<std::endl;

                return cast_ray(collision, reflected, r_depth + 1);
            }

            return Vec3();
        }
    }


    template <class T>
    inline std::tuple<bool, Vec3, T*> find_neatest(const Vec3& src, const Vec3& dir,
                                                      const std::vector<T>& solids) {
        std::cout<< "3"<<std::endl;

        if (!solids.empty()) {
            bool flag = false;
            Vec3 collision = Vec3();
            T* near_solid = nullptr;

            double min_distance = std::numeric_limits<double>::max();
            for (auto solid : solids) {
                Vec3 lcal_collision = Vec3(-1, -1 ,-1);
                bool have_collision = false;
                std::tie(have_collision, lcal_collision) = solid.collision(src, dir);

                if(have_collision){
                    double range = Vec3::range(src, lcal_collision);
        std::cout<< "lcal_collision "<<lcal_collision<<std::endl;
        std::cout<< "src"<< src<<std::endl;

        std::cout<< "ramge : "<< range<<std::endl;

                    flag = true;
                    if (range < min_distance){
                        min_distance = range;
                        near_solid = &solid;
                        collision = lcal_collision;
                    }
                }
            }
            std ::cout << "c : "<<std::endl;

            return std::make_tuple<bool, Vec3, T*>(std::move(flag), std::move(collision), std::move(near_solid));
        } else {
            return std::make_tuple<bool, Vec3, T*>(std::move(false), std::move(Vec3()), std::move(nullptr));
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
