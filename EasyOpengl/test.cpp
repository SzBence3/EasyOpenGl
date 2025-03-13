#include"Vertex.h"

int main() {
    eogl::Vertex<3, 2, 3> v;
    v = {glm::vec3(1,2,3), glm::vec2(1,2), glm::vec3(1,2,3)};
    return 0;
}