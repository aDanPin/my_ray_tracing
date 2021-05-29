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
        framebuffer = std::vector<Vec3>(camera.width * camera.height);
        for (size_t j = 0; j < camera.height; j++) {
            for (size_t i = 0; i < camera.width; i++) {
                framebuffer[i+j*camera.width] = Vec3(
                    255. * (camera.height - j) / camera.height,
                    255. * (camera.height - j) / camera.height,
                    255. * (camera.height - j) / camera.height
                );
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

                Vec3 pixel = cast_ray(camera.position, dir);

                if (pixel != Vec3(-1, -1, -1)) {
                    framebuffer[i+j*camera.width] = pixel;
                    std::cout<<framebuffer[i+j*camera.width]<<std::endl;
                }

            // std::cout<<"I: "<< i<<" J: "<<j<<std::endl;
            }
        }
    }

    const int RECURSION_DEPTH = 255;
    const double ABSORPTION_COEF = 0.5;
    const Vec3 LIGHT_VECTOR = Vec3(255, 255, 255);


    Vec3 cast_ray(const Vec3& src, const Vec3& dir, int r_depth = 0) {
        // std::cout<<"Depth: "<< r_depth<<std::endl;
        if (  r_depth >= RECURSION_DEPTH){
            return LIGHT_VECTOR * std::pow( ABSORPTION_COEF, r_depth );
        }
        else{
            // find
            bool got_l_collision = false;
            Vec3 lCollision;
            size_t nearLSolid = 0;

            std::tie(got_l_collision, lCollision, nearLSolid) =
                                                    find_neatest<LightSphere>(src, dir, lSpheres);

            if(got_l_collision){
                nearLSolid = 0;
                return LIGHT_VECTOR * std::pow(ABSORPTION_COEF, r_depth);
            }

            bool got_collision = false;
            Vec3 collision;
            size_t nearSolid = 0;

            std::tie(got_collision, collision, nearSolid) = find_neatest<Sphere>(src, dir, spheres);

            if(got_collision){
                // продолжить рекурсию
                // найти новую точку отражения
                Vec3 reflected  = spheres[nearSolid].reflection(src, dir, collision);
                //std::cout<< "Reflection: from" << std::endl;
                //std::cout << collision.x << ' '<< collision.y << ' '<< collision.z << ' ' << std::cout;
                //std::cout << Vec3()<< std::endl;
                return cast_ray(collision, reflected, r_depth + 1);
            }

            if (r_depth == 0){
                return Vec3(-1, -1, -1);
            } else {
                Vec3 ans = LIGHT_VECTOR * std::pow( ABSORPTION_COEF, r_depth );
                return Vec3();
            }
        }
    }


    template <class T>
    inline std::tuple<bool, Vec3, size_t> find_neatest(const Vec3& src, const Vec3& dir,
                                                      const std::vector<T>& solids) {
        if (!solids.empty()) {
            bool flag = false;
            Vec3 collision = Vec3();
            size_t near_solid = 0;

            double min_distance = std::numeric_limits<double>::max();
            for (size_t i = 0; i <  solids.size(); ++i) {
                Vec3 lcal_collision = Vec3(-1, -1 ,-1);
                bool have_collision = false;
                std::tie(have_collision, lcal_collision) = solids[i].collision(src, dir);

                if(have_collision){
                    double range = Vec3::range(src, lcal_collision);

                    flag = true;
                    if (range < min_distance){
                        min_distance = range;
                        near_solid = i;
                        collision = lcal_collision;
                    }
                }
            }

            return std::make_tuple<bool, Vec3, size_t>(std::move(flag), std::move(collision), std::move(near_solid));
        } else {
            return std::make_tuple<bool, Vec3, size_t>(std::move(false), std::move(Vec3()), std::move(0));
        }
    }

    void write() {
        std::ofstream ofs; // save the framebuffer to file
        ofs.open(path);
        ofs << "P6\n" << camera.width << " " << camera.height << "\n255\n";
        for (size_t i = 0; i < camera.height * camera.width; ++i) {
            std::cout << framebuffer[i] << std::endl;
            // ofs << (char)(255 * std::max(0., std::min(1., framebuffer[i].x)))
            //     << (char)(255 * std::max(0., std::min(1., framebuffer[i].y)))
            //     << (char)(255 * std::max(0., std::min(1., framebuffer[i].z)));
            ofs << (char)(std::trunc(framebuffer[i].x))
                << (char)(std::trunc(framebuffer[i].y))
                << (char)(std::trunc(framebuffer[i].z));

        }
        ofs.close();
    }
};

#endif // SCENE_HPP
