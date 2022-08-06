#include <iostream>

#include "Application.h"
#include "Display.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "DrawObject.h"

const std::string vertexShaderSource =
"#version 330 core\n"
"\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec4 colour;\n"
"flat out vec4 vertexColour;\n"
"\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"   vertexColour = colour;"
"}\0";

const std::string fragmentShaderSource =
"#version 330 core\n"
"\n"
"flat in vec4 vertexColour;\n"
"out vec4 outColor;\n"
"\n"
"void main()\n"
"{\n"
"   outColor = vertexColour;\n"
"}\0";

//
// Error checking functions.
//

void GLClearError()
{
    while (auto error = glGetError())
        if (!error) break;
}

bool GLLogCall()
{
    while (GLenum error = glGetError()) {
        std::cerr << "[OpenGL Error] " << error << std::endl;
        return false;
    }
    return true;
}


// Returns 0 if initialization failed, otherwise returns 1.
static int initializeGLFW()
{
    if (!glfwInit())
        return 0;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    return 1;
}


static unsigned int compileShader(const std::string& source, unsigned int type)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*) _malloca(length * sizeof(char));
        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cerr << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}


static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}



// Calls glDrawElements with the provided vao and ebo bound.
static void printObject(unsigned int vao, unsigned int ebo, unsigned int* indices, int count)
{
    GLCall(glBindVertexArray(vao));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    GLCall(glViewport(0, 0, width, height));
}

void processInput(const Display &display)
{
    if (glfwGetKey(display.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(display.getWindow(), true);
    }
}

int main()
{
    if (!initializeGLFW())
        return 1;

    Display display(800, 600, "LearnOpenGL");
    display.createContext(framebuffer_size_callback);
    //GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    //if (window == NULL) {
    //    return 1;
    //}
    //glfwMakeContextCurrent(display.getWindow());
    //glfwSetFramebufferSizeCallback(display.getWindow(), framebuffer_size_callback);
    
 
    // Load OpenGL function pointers.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;

    // Setup data
    float vertices_t[] = {
        // 0
        -0.5f, -0.5f, 0.0f,
        0.196f, 0.804f, 0.196f, 1.0f,
        // 1
        -0.3f, -0.5f,  0.0f,
        0.8f, 0.0f, 0.1f, 1.0f,
        // 2
        -0.3f, 0.3f, 0.0f,
        0.196f, 0.804f, 0.196f, 1.0f,
        // 3
        -0.5f, 0.3f, 0.0f,
        0.8f, 0.0f, 0.1f, 1.0f,
        // 4
        -0.9f, 0.3f, 0.0f,
        0.196f, 0.804f, 0.196f, 1.0f,
        // 5
        -0.9f, 0.5f, 0.0f,
        0.8f, 0.0f, 0.1f, 1.0f,
        // 6
        0.1f, 0.5f, 0.0f,
        0.196f, 0.804f, 0.196f, 1.0f,
        // 7
        0.1f, 0.3f, 0.0f,
        0.8f, 0.0f, 0.1f, 1.0f
    };
    float vertices_f[] = {
        // 0
         0.2f, -0.5f,  0.0f,
         0.8f, 0.0f, 0.1f, 1.0f,
        // 1
         0.4f, -0.5f,  0.0f,
         0.8f, 0.0f, 0.1f, 1.0f,
        // 2
         0.4f, -0.1f,  0.0f,
         0.8f, 0.0f, 0.1f, 1.0f,
        // 3
         0.7f, -0.1f,  0.0f,
         0.8f, 0.0f, 0.1f, 1.0f,
        // 4
         0.7f,  0.1f,  0.0f,
         0.8f, 0.0f, 0.1f, 1.0f,
        // 5
         0.4f,  0.1f,  0.0f,
         0.196f, 0.804f, 0.196f, 1.0f,
        // 6
         0.4f,  0.3f,  0.0f,
         0.196f, 0.804f, 0.196f, 1.0f,
        // 7
         0.9f,  0.3f,  0.0f,
         0.8f, 0.0f, 0.1f, 1.0f,
        // 8
         0.9f,  0.5f,  0.0f,
         0.8f, 0.0f, 0.1f, 1.0f,
        // 9
         0.4f,  0.5f,  0.0f,
         0.196f, 0.804f, 0.196f, 1.0f,
        // 10
         0.2f,  0.5f,  0.0f,
         0.196f, 0.804f, 0.196f, 1.0f,
         // 11
         0.4f,  0.5f,  0.0f,
         0.8f, 0.0f, 0.1f, 1.0f
    };
    unsigned int model_t[] = {
        0, 1, 2,
        0, 2, 3,
        4, 7, 6,
        4, 6, 5
    };
    unsigned int model_f[] = {
        0, 1, 11,
        0, 9, 10,
        2, 3, 4,
        2, 4, 5,
        6, 7, 8,
        6, 8, 9
    };
    GLCall(glClearColor(0.71f, 0.44f, 0.76f, 1.0f));

    // T Buffer Object initialization
    VertexBuffer t_vbo(vertices_t, sizeof(vertices_t));
    ElementBuffer t_ebo(model_t, 12);
    DrawObject t_object(&t_vbo, &t_ebo);
    
    // F Buffer Object intialization
    VertexBuffer f_vbo(vertices_f, sizeof(vertices_f));
    ElementBuffer f_ebo(model_f, 18);
    DrawObject f_object(&f_vbo, &f_ebo);

    // Register and compile shader.
    unsigned int t_shader = createShader(vertexShaderSource, fragmentShaderSource);
    GLCall(glUseProgram(t_shader));

    // Run the application loop.
    while (!display.shouldClose()) {
        // input
        processInput(display);

        // render
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        t_object.draw();
        f_object.draw();

        // poll events
        glfwSwapBuffers(display.getWindow());
        glfwPollEvents();
    }
    GLCall(glDeleteProgram(t_shader));
    

    return 0;
}