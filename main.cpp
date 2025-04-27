#include "headers/headers.h"

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

    {
        const GLFWvidmode *mode = glfwGetVideoMode (monitor);

        screenWidth = mode->width;
        screenHeight = mode->height;
    }

    GLFWwindow *window = glfwCreateWindow (((3 * screenWidth) / 4), ((3 * screenHeight) / 4), "ver.0.0", NULL, NULL);
    glfwMakeContextCurrent (window);
    glfwGetWindowSize (window, &windowWidth, &windowHeight);
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
    uniformProjection = glGetUniformLocation (sProgram, "uProjection");
    
    glm::mat4 projection = glm::ortho (-((float)windowWidth / windowHeight), ((float)windowWidth / windowHeight), -1.0f, 1.0f, 0.1f, 100.0f);
    glUniformMatrix4fv (uniformProjection, 1, GL_FALSE, glm::value_ptr (projection));

    glfwSetCursorPosCallback (window, cursor_position_callback);
    glfwSetMouseButtonCallback (window, mouse_button_callback);

    while (!glfwWindowShouldClose (window))
    {
        glClearColor (0.65, 0.65, 0.65, 1.0);
        glClear (GL_COLOR_BUFFER_BIT);

        glm::mat4 model (1.0f);
        model = glm::translate (model, glm::vec3 (X, Y, -1.0f));

        glUniformMatrix4fv (uniformModel, 1, GL_FALSE, glm::value_ptr (model));

        glBindVertexArray (VAO);
        glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        if (!isDragging)
        {
            Y = Y + -G * t * t;

            if (Y <= -0.85f)
            {
                Y = -0.85f;
                t = 0;
            }
    
            t++;
        }

        glfwSwapBuffers (window);
        glfwPollEvents ();
    }

    glDeleteVertexArrays (1, &VAO);
    glDeleteBuffers (1, &VBO);
    glDeleteBuffers (1, &EBO);
    glDeleteProgram (sProgram);

    glfwTerminate ();
}