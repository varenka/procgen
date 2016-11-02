#ifndef BITLEAF_H
#define BITLEAF_H
#include "mesh.h"
#include <random>

class Bitleaf
{
public:

    ///RNG functions
    static float randf(float, float);
    static glm::vec3 randxz(float, float, float);

    ///Construction functions: tools for creating 3d shapes from vertices
    static IndexedModel CreateQuad(glm::vec3, glm::vec3, glm::vec3, glm::vec3);

    ///Procedural functions that generate entire randomized meshes
    static Mesh RandomGrass();
};

#endif // BITLEAF_H
