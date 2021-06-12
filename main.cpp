#include "scene.hpp"
#include "vector.hpp"
#include <chrono>

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

    scene.add(LightSphere(Vec3(-1000 , -1000, -1000), 1));

    scene.add(LightSphere(Vec3(-100, 1024 + 20, 0), 30));

    scene.add(Sphere(Vec3(-1000 , -1000, -1000), 1));

    scene.add(Sphere(Vec3(0, 1536 + 256, -1408 + 512), 1024));
    scene.add(Sphere(Vec3(-100, 1024 + 100, -100), 50));
    scene.add(Sphere(Vec3(0, 1024 + 100, 0), 100));

    auto start = std::chrono::steady_clock::now();
    scene.render();
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Rendering time: " << elapsed.count() << std::endl;

    scene.write();
}
