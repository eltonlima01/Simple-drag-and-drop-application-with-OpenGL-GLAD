#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define G 0.000025

int t = 0;

float vertices [] =
{
    -0.15f, 0.15f, 0.0f, // 0
    1.0f, 0.0f, 0.0f,

    -0.15f, -0.15f, 0.0f, // 1
    0.5f, 0.5f, 0.0f,

    0.15f, -0.15f, 0.0f, // 2
    0.0f, 0.5f, 0.5f,

    0.15f, 0.15f, 0.0f, // 3
    0.0f, 0.0f, 1.0f
};

float Y = 0.0f;

unsigned int indices [] =
{
    0, 1, 2,
    0, 3, 2
};

const char *vShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 vPos;\n"
"layout (location = 1) in vec3 vColor;\n"
"out vec3 fColor;\n"
"uniform mat4 uModel;\n"
"uniform mat4 uProjection;\n"
"void main (){\n"
"gl_Position = uProjection * uModel * vec4 (vPos, 1.0f);\n"
"fColor = vColor;\n"
"}",

*fShaderSource =
"#version 330 core\n"
"in vec3 fColor;\n"
"out vec4 FragColor;\n"
"void main (){\n"
"FragColor = vec4 (fColor, 1.0f);\n"
"}";

void framebuffer_size_callback (GLFWwindow *window, int width, int height);
void get_monitor_dimensions ();

int main ()
{
    glfwInit ();

    {    
        glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
            glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }

    GLFWmonitor *monitor = glfwGetPrimaryMonitor ();
    int screenWidth, screenHeight;

    {
        const GLFWvidmode *mode = glfwGetVideoMode (monitor);

        screenWidth = mode->width;
        screenHeight = mode->height;
    }

    GLFWwindow *window = glfwCreateWindow (((3 * screenWidth) / 4), ((3 * screenHeight) / 4), "ver.0.0", NULL, NULL);
    glfwMakeContextCurrent (window);
    glfwSetFramebufferSizeCallback (window, framebuffer_size_callback);

    gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress);

    unsigned int vShader = glCreateShader (GL_VERTEX_SHADER),
    fShader = glCreateShader (GL_FRAGMENT_SHADER),
    sProgram = glCreateProgram ();

    {    
        glShaderSource (vShader, 1, &vShaderSource, NULL);
        glShaderSource (fShader, 1, &fShaderSource, NULL);

        glCompileShader (vShader);
        glCompileShader (fShader);

        glAttachShader (sProgram, vShader);
        glAttachShader (sProgram, fShader);
        glLinkProgram (sProgram);

        glDeleteShader (vShader);
        glDeleteShader (fShader);
    }

    unsigned int VAO, VBO, EBO;

    {
        glGenVertexArrays (1, &VAO);
        glBindVertexArray (VAO);

        glGenBuffers (1, &VBO);
        glBindBuffer (GL_ARRAY_BUFFER, VBO);
        glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers (1, &EBO);
        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, (6 * sizeof (float)), (void*)0);
        glEnableVertexAttribArray (0);

        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof (float)), (void*)(3 * sizeof (float)));
        glEnableVertexAttribArray (1);
    }

    glUseProgram (sProgram);

    unsigned int uniformModel = glGetUniformLocation (sProgram, "uModel");
    unsigned int uniformProjection = glGetUniformLocation (sProgram, "uProjection");

    glm::mat4 projection = glm::ortho (-((float)screenWidth / screenHeight), ((float)screenWidth / screenHeight), -1.0f, 1.0f, 0.1f, 100.0f);

    while (!glfwWindowShouldClose (window))
    {
        glClearColor (0.65, 0.65, 0.65, 1.0);
        glClear (GL_COLOR_BUFFER_BIT);

        Y = Y + -G * t * t;

        glm::mat4 model (1.0f);
        model = glm::translate (model, glm::vec3 (0.0f, Y, -1.0f));

        glUniformMatrix4fv (uniformModel, 1, GL_FALSE, glm::value_ptr (model));
        glUniformMatrix4fv (uniformProjection, 1, GL_FALSE, glm::value_ptr (projection));

        glBindVertexArray (VAO);
        glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        if (Y <= -0.85f)
        {
            Y = -0.85f;
            t = 0;
        }

        t++;

        glfwSwapBuffers (window);
        glfwPollEvents ();
    }

    glDeleteVertexArrays (1, &VAO);
    glDeleteBuffers (1, &VBO);
    glDeleteBuffers (1, &EBO);
    glDeleteProgram (sProgram);

    glfwTerminate ();
}

void framebuffer_size_callback (GLFWwindow *window, int width, int height)
{
    glViewport (0, 0, width, height);
}