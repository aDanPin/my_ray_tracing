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
    scene.add(LightSphere(Vec3(0, 256 + 40, 50), 5));

    scene.add(Sphere(Vec3(-40, 256 + 40, -60), 40));
    scene.add(Sphere(Vec3( 40, 256 + 40, -60), 40));

    scene.render();
    scene.write();
}
