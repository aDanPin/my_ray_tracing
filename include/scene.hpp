#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <cmath>
#include <limits>

#include <omp.h>

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

    const int RAY_IN_PIXEL = 8;

    void render() {
        #pragma omp parallel for
        for (int j = 0; j < camera.height; j++) {
            #pragma omp parallel for
            for (int i = 0; i < camera.width; i++) {
                std::vector<Vec3> pixels;

                for (int ii = 0; ii < RAY_IN_PIXEL; ii ++) {
                    for (int jj = 0; jj < RAY_IN_PIXEL; jj ++) {
                        double x = (camera.width / 2) *
                                    ((double)(i - camera.width/2) / (camera.width / 2)) + (ii/RAY_IN_PIXEL);
                        double z = (camera.height / 2) *
                                    ((double)(camera.height/2 - j) / (camera.height / 2)) + (jj/RAY_IN_PIXEL);

                        Vec3 stc = camera.position;
                        Vec3 dir =  Vec3(x, camera.distance, z);
                        dir = approx(dir, camera.distance);

                        Vec3 pixel = cast_ray(stc, approx(dir, 1));

                        if (pixel != Vec3(-1, -1, -1)) {
                            pixels.push_back(pixel);
                        }
                    }
                }

                Vec3 result_pixel(0,0,0);
                for(int ii = 0; ii < pixels.size(); ii++)
                    result_pixel = result_pixel + pixels[ii];

                result_pixel = result_pixel / pixels.size();
                framebuffer[i+j*camera.width] = result_pixel;
            }
        }
    }

    const int RECURSION_DEPTH = 255;
    const double ABSORPTION_COEF = 0.65;
    const Vec3 LIGHT_VECTOR = Vec3(255, 255, 255);
    const double MIN_DELTA =  0.001;
    const double MAX_DOUBLE = std::numeric_limits<double>::max();

    Vec3 cast_ray(const Vec3& src, const Vec3& dir, int r_depth = 0, int do_not_touch = -1) {
        if (  r_depth >= RECURSION_DEPTH){
            return Vec3(100, 100, 100) * std::pow(ABSORPTION_COEF, r_depth);
        }
        else{
            bool light_collision_was;
            Vec3 light_collision;
            size_t light_num;
            double light_dist;
            std::tie(light_collision_was, light_collision, light_num, light_dist) =
                        find_neatest<LightSphere>(src, dir, lSpheres);

            bool collision_was;
            Vec3 collision;
            size_t num;
            double dist;
            std::tie(collision_was, collision, num, dist) =
                        find_neatest<Sphere>(src, dir, spheres, do_not_touch);

            if ( light_collision_was && collision_was) {
                if ( light_dist <= dist) {
                    return Vec3(255, 255, 255) * std::pow(ABSORPTION_COEF, r_depth);
                } else {
                    Vec3 reflection = spheres[num].reflection(src, dir, collision);

                    return cast_ray(collision, collision + reflection, r_depth +1, num);
                }
            } else if (light_collision_was) {
                return Vec3(255, 255, 255) * std::pow(ABSORPTION_COEF, r_depth);
            } else if (collision_was) {
                    Vec3 reflection = spheres[num].reflection(src, dir, collision);

                    return cast_ray(collision, collision + reflection, r_depth +1, num);
            }

            if ( r_depth == 0)
                return Vec3(-1, -1, -1);
            else
                return Vec3(200, 200, 200) * std::pow(ABSORPTION_COEF, r_depth);
        }
    }


    template <class T>
    inline std::tuple<bool, Vec3, size_t, double> find_neatest(const Vec3& src, const Vec3& dir,
                                                      const std::vector<T>& solids, int do_not_touch = -1) {
            double distance = MAX_DOUBLE;
            bool collision_was = false;
            size_t num_solid;
            Vec3 collision;

            for(int i = 0; i < solids.size(); i++) {
                if (i == do_not_touch)
                    continue;

                Vec3 local_collision;
                bool local_collision_was;
                std::tie(local_collision_was, local_collision) =
                    solids[i].collision(src, dir);

                if (local_collision_was) {
                    double local_distance =  Vec3::range(src, local_collision);
                    if (local_distance < distance) {
                        collision_was = true;
                        distance = local_distance;
                        collision = local_collision;
                        num_solid = i;
                    }
                }
            }

            return std::make_tuple<bool, Vec3, size_t, double>
                (std::move(collision_was), std::move(collision), std::move(num_solid), std::move(distance));
    }

    void write() {
        std::ofstream ofs;
        ofs.open(path);
        ofs << "P6\n" << camera.width << " " << camera.height << "\n255\n";
        for (size_t i = 0; i < camera.height * camera.width; ++i) {
            ofs << (char)(std::trunc(framebuffer[i].x))
                << (char)(std::trunc(framebuffer[i].y))
                << (char)(std::trunc(framebuffer[i].z));

        }
        ofs.close();
    }
};

#endif // SCENE_HPP
