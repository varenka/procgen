#include <iostream>
#include <GL/glew.h>
#include <ctime>
#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "bitleaf.h"

#define WIDTH 800
#define HEIGHT 600

using namespace std;

IndexedModel TCreateQuad(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4)
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

int main(int argc, char* argv[])
{
    srand(time(NULL));
    ///Start setup timer
    clock_t start;
    start = clock();

    Window window(WIDTH, HEIGHT, "Test");

    Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
                          Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
                          Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

    unsigned int indices[] = { 0, 1, 2 };

    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
    Mesh mesh2("./res/monkey3.obj");
    Mesh quad = TCreateQuad(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Shader shader("./res/basicShader");

    Texture texture("./res/bricks.jpg");

    Transform transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

    Camera camera(glm::vec3(0, 0, -3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

    /// End setup timer
    double duration;
    duration = ( clock() - start ) / (double)CLOCKS_PER_SEC;
    cout << "Total time taken for setup: " << duration << "s" << endl;

    float counter = 0.0f;

    while(!window.IsClosed())
    {
        ///Start frame timer
        start = clock();

        float sinCounter = sinf(counter);
        float cosCounter = cosf(counter);

        window.Clear(0.0f, 0.15f, 0.15f, 1.0f);

//        transform.GetPos().x = sinCounter;
//        transform.GetRot().x = counter;
        transform.GetRot().y = counter;
//        transform.GetRot().z = counter;
//        transform.GetPos().z = sinCounter;
//        transform.SetScale(glm::vec3(cosCounter + 1, cosCounter + 1, cosCounter + 1));

        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera);
        quad.Draw();

        window.Update();
        counter += 0.01f;
        ///Stop frame timer
        duration = ( clock() - start ) / (double)CLOCKS_PER_SEC;
        cout << 1 / duration << " fps" << endl;
    }

    return 0;
}
