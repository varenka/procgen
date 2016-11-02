#ifndef PROCGEN_H
#define PROCGEN_H
#include "mesh.h"
#include <random>

class Procgen
{
public:
    Procgen() {}

    static glm::vec3 vrandom();
    static Mesh RandomGrass();
};

#endif // PROCGEN_H
