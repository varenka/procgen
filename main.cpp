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

int main(int argc, char* argv[])
{
    srand(time(NULL));
    ///Start setup timer
    clock_t start;
    start = clock();

    Window window(WIDTH, HEIGHT, "Test");

    Vertex vertices[] = { Vertex(glm::vec3(0, 1, 0), glm::vec2(0, 0)),
                          Vertex(glm::vec3(0, 0, 0), glm::vec2(0.5, 1.0)),
                          Vertex(glm::vec3(1, 0, 0), glm::vec2(1.0, 0.0)),
                          Vertex(glm::vec3(1, 1, 0), glm::vec2(1.0, 0.0))
                        };

    unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };

    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
    //Mesh mesh2("./res/monkey3.obj");

    /*
    Mesh quad;
    quad.AddModel(Bitleaf::CreateQuad(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    */
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
        mesh.Draw();

        window.Update();
        counter += 0.01f;
        ///Stop frame timer
        duration = ( clock() - start ) / (double)CLOCKS_PER_SEC;
        cout << 1 / duration << " fps" << endl;
    }

    return 0;
}
