#include "scene.hpp"
#include "vector.hpp"

int main(){
    std::string path ="/home/adanpin/develop/study/diploma/data/out.ppm";

    Camera camera(256, 256, Vec3f(0., 0., 0.), Vec3f(1., 0., 0.), 256.);
    Scene scene(camera, path);

    scene.add(Sphere(Vec3f(512, 0, 0), 100));

    scene.render();

    scene.write();
}
