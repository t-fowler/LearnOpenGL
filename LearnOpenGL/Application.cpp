#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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


static unsigned int compileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) _malloca(length * sizeof(char));
        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cerr << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}


static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

static void printObject(unsigned int vbo, unsigned int vao, unsigned int ebo, int* indices)
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, indices);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    // Initialize the library.
    if (!glfwInit())
        return -1;

    // Create OpenGL context and create a window.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
 
    // Load OpenGL function pointers.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;

    // Setup data
    float vertices_t[] = {
        -0.5f, -0.5f,  0.0f,
        0.196f, 0.804f, 0.196f, 1.0f,
        -0.3f, -0.5f,  0.0f,
        0.8f, 0.0f, 0.1f, 1.0f,
        -0.3f,  0.3f,  0.0f,
        0.196f, 0.804f, 0.196f, 1.0f,
        -0.5f,  0.3f,  0.0f,
        0.8f, 0.0f, 0.1f, 1.0f,
        -0.9f,  0.3f,  0.0f,
        0.196f, 0.804f, 0.196f, 1.0f,
        -0.9f,  0.5f,  0.0f,
        0.8f, 0.0f, 0.1f, 1.0f,
         0.1f,  0.5f,  0.0f,
        0.196f, 0.804f, 0.196f, 1.0f,
         0.1f,  0.3f,  0.0f,
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
    glClearColor(0.71f, 0.44f, 0.76f, 1.0f);

    // T Buffer Object initialization
    unsigned int t_vbo, t_vao, t_ebo;
    glGenVertexArrays(1, &t_vao);
    glGenBuffers(1, &t_vbo);
    glGenBuffers(1, &t_ebo);

    glBindVertexArray(t_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, t_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_t), vertices_t, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model_t), model_t, GL_STATIC_DRAW);

    // Configure how OpenGL will interpret buffer data.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // F Buffer Object intialization
    unsigned int f_vbo, f_vao, f_ebo;
    glGenVertexArrays(1, &f_vao);
    glGenBuffers(1, &f_vbo);
    glGenBuffers(1, &f_ebo);

    glBindVertexArray(f_vao);

    glBindBuffer(GL_ARRAY_BUFFER, f_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_f), vertices_f, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model_f), model_f, GL_STATIC_DRAW);

    // Configure how OpenGL will interpret buffer data.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Register and compile shader.
    unsigned int t_shader = createShader(vertexShaderSource, fragmentShaderSource);
    unsigned int f_shader = createShader(vertexShaderSource, fragmentShaderSource);

    // Run the application loop.
    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // render
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(t_shader);
        glBindVertexArray(t_vao);
        glBindBuffer(GL_ARRAY_BUFFER, t_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t_ebo);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
        glUseProgram(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glUseProgram(f_shader);
        glBindVertexArray(f_vao);
        glBindBuffer(GL_ARRAY_BUFFER, f_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_ebo);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);
        glUseProgram(0);
        
        //glBindVertexArray(f_vao);
        //glBindBuffer(GL_ARRAY_BUFFER, f_vbo);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_ebo);
        //glDrawElements(GL_TRIANGLES, 18, GL_INT, model_f);

        // poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(t_shader);
    glfwTerminate();

    return 0;
}