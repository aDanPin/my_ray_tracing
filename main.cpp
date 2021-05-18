

#include "scene.hpp"
#include "vector.hpp"

int main(){
    std::string path ="/home/adanpin/develop/study/diploma/data/out.ppm";

    Scene scene(256, 256, path);
    scene.write();
}
