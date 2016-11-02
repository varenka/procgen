#include "bitleaf.h"

float Bitleaf::randf(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float> (RAND_MAX / (max - min)));
}

/**
Returns a glm::vec3 with:
    an x on the interval [-x, x]
    a z on the interval [-z, z]
    and does not change y
**/
glm::vec3 Bitleaf::randxz(float x, float y, float z)
{
    /*
    glm::vec3 r;
    r.x = randf(min, max);
    r.z = randf(min, max);
    return r;
    */
    return glm::vec3(randf(-x, x), y, randf(-z, z));
}
///TODO: TexCoords
IndexedModel CreateQuad(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4)
{
    IndexedModel model;

    model.positions.push_back(v1);
    model.positions.push_back(v2);
    model.positions.push_back(v3);
    model.positions.push_back(v4);

    ///First tri: (v1, v3, v4)
    model.indices.push_back(0);
    model.indices.push_back(2);
    model.indices.push_back(3);

    ///Second tri: (v1, v2, v4)
    model.indices.push_back(0);
    model.indices.push_back(1);
    model.indices.push_back(3);

    ///Make all texCoords 0 for now
    for(int i = 0; i < 4; i++)
        model.texCoords.push_back(glm::vec2(0.0f, 0.0f));

    model.normals.reserve(4);
    model.CalcNormals();
}

Mesh Bitleaf::RandomGrass()
{
    IndexedModel model;
    Mesh m = Mesh();
    return m;
}
