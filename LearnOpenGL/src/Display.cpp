#include "Display.h"


const char* ConstructorException::what() const throw()
{
    return "GLFW error: Display failed to construct window";
}


Display::Display(int width, int height, std::string title)
{
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL) {
        throw new ConstructorException;
    }
}

Display::~Display()
{
    glfwTerminate();
}

int Display::shouldClose()
{
    return glfwWindowShouldClose(window);
}

void Display::createContext(GLFWframebuffersizefun framebuffer_size_callback)
{
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}