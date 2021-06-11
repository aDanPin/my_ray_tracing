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

    Camera camera(256, 256, Vec3(0, 0, 0), Vec3(0., 1., 0.), 1024);
    Scene scene(camera, path);

    scene.add(LightSphere(Vec3(0 , -1, 0), 0));
    // Sun
    scene.add(LightSphere(Vec3(-100, 1024 + 20, 0), 30));

    scene.add(Sphere(Vec3(0, 1024 + 100, 0), 100));
    scene.add(Sphere(Vec3(-100, 1024 + 100, -100), 50));
    scene.add(Sphere(Vec3(0, 1536 + 256, -1408 + 512), 1024));

    scene.render();
    scene.write();
}
