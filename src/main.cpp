#include <glad/glad.h>
#include <GLFW/glfw3.h>]
#include "Render/ShaderRender.h"
#include "Resource/ResourceManager.h"
#include <iostream>

class WindowContext {
private:
    static unsigned short window_widht;
    static unsigned short window_height;
public:
    static void WindowSizeCallback(GLFWwindow* window, int widgh, int height) {
        window_widht = widgh;
        window_height = height;
        glViewport(0, 0, window_widht, window_height);
    }
};

unsigned short WindowContext::window_widht = 640;
unsigned short WindowContext::window_height = 480;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char** argv) {
    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // checking OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Snake", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, WindowContext::WindowSizeCallback);
    glfwSetKeyCallback(window, KeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "Can't load GLAD!" << std::endl;
        return -1;
    }

    std::cout << "Render - " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version - " << glGetString(GL_VERSION) << std::endl;

    glClearColor(1, 1, 1, 1);

    {
        Resource::ResourceManager resource(argv[0]);
        std::shared_ptr<Render::ShaderRender> defaultShader =
            resource.LoadShader("DefaultShader", "resource/shaders/vertex_shader.txt", "resource/shaders/fragment_shader.txt");

        float points[] = { 0.0, 0.5, 0.0,
                          -0.5, 0.0, 0.0,
                           0.5, 0.0, 0.0 };
        GLuint points_vbo;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        float colors[] = { 1.0, 0.0, 0.0,
                           0.0, 1.0, 0.0,
                           0.0, 0.0, 1.0 };
        GLuint color_vbo;
        glGenBuffers(1, &color_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            defaultShader->Use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}