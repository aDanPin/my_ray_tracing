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
    scene.add(LightSphere(Vec3(0, 256 + 40, 0), 35));

    scene.add(Sphere(Vec3(-50, 256 + 60, -70), 40));
    scene.add(Sphere(Vec3( 50, 256 + 40,  70), 40));
    scene.add(Sphere(Vec3( 60, 256 + 30, -80), 40));

    scene.render();
    scene.write();
}
