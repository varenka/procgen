#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>
#include <iostream>

using namespace std;

class Window
{
public:
    Window(int width, int height, const string& title);

    void Clear(float r, float g, float b, float a);
    void Update();
    bool IsClosed();

    virtual ~Window();
private:
    Window(const Window& other) {}
    void operator=(const Window& other) {}

    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    bool m_closed;
};

#endif // WINDOW_H
