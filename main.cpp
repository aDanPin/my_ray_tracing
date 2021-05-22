#include "scene.hpp"
#include "vector.hpp"

//       z
//       ^
//       |
//       |
//       |
//       |
//       *----------------->y
//      /
//     /
//    /
//  x

// Camera -> {0, 1, 0}


int main(){
    std::string path ="/home/adanpin/develop/study/diploma/data/out.ppm";

    Camera camera(256, 256, Vec3(0., 0., 0.), Vec3(0., 1., 0.), 256.);
    Scene scene(camera, path);

    // Sun
    scene.add(Sphere(Vec3(13, 256 + 12, 120), 5));

    scene.add(Sphere(Vec3(13, 256 + 40, 13), 27));
    scene.add(Sphere(Vec3(90, 256 + 50, -60), 30));
    scene.add(Sphere(Vec3(-70,256 + 30, -80), 40));
//    scene.add(Sphere(Vec3(-30,256 + 30, 40), 25));

    scene.render();

    scene.write();
}
