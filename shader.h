#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include "transform.h"
#include "camera.h"

using namespace std;

class Shader
{
public:
    Shader(const string& fileName);

    void Bind();
    void Update(const Transform& transform, const Camera& camera);

    virtual ~Shader();
private:
    static const unsigned int NUM_SHADERS = 2;
    Shader(const Shader& other) {}
    void operator=(const Shader& other) {}

    enum
    {
        TRANSFORM_U,

        NUM_UNIFORMS
    };

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // SHADER_H
