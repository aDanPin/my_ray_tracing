#include "scene.hpp"
#include "vector.hpp"

//       z
//       ^
//       |
//       |
//       |
//       |
//       ------------------>y
//      /
//     /
//    /
//  x

// Camera -> {0, 1, 0}


int main(){
    std::string path ="/home/adanpin/develop/study/diploma/data/out.ppm";

    Camera camera(256, 256, Vec3(0., 0., 0.), Vec3(0., 1., ), 256.);
    Scene scene(camera, path);

    scene.add(Sphere(Vec3(0, 512, 0), 10));

    scene.render();

    scene.write();
}
