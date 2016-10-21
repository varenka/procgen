#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>
#include "stb_image.h"

using namespace std;

class Texture
{
public:
    Texture(const string& fileName);

    void Bind(unsigned int unit);

    virtual ~Texture();
private:
    Texture(const Texture& other) {}
    void operator=(const Texture& other) {}

    GLuint m_texture;
};

#endif // TEXTURE_H
