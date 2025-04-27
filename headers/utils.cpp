#define G 0.000025

int t = 0;
int success;
int screenWidth, screenHeight,
windowWidth = 0, windowHeight = 0;

char infoLog [512];

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

float X = 0.0f, Y = 0.0f;
float dragOffSetX = 0.0f, dragOffSetY = 0.0f;
float mouseX = 0.0f, mouseY = 0.0f,
lastMouseX = 0.0f, lastMouseY = 0.0f;

unsigned int indices [] =
{
    0, 1, 2,
    0, 3, 2
};
unsigned int uniformProjection;

bool isDragging = false;

void framebuffer_size_callback (GLFWwindow *window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glViewport (0, 0, width, height);

    glm::mat4 projection = glm::ortho (-((float)width / height), ((float)width / height), -1.0f, 1.0f, 0.1f, 100.0f);
    glUniformMatrix4fv (uniformProjection, 1, GL_FALSE, glm::value_ptr (projection));

}

void cursor_position_callback (GLFWwindow *window, double xPos, double yPos)
{
    mouseX = xPos;
    mouseY = yPos;

    if (isDragging && windowWidth > 0 && windowHeight > 0)
    {
        float mouseX0 = (2.0f * mouseX / windowWidth) - 1.0f;
        float mouseY0 = 1.0f - (2.0f * mouseY / windowHeight);

        mouseX0 *= (float)windowWidth / windowHeight;

        X = mouseX0 + dragOffSetX;
        Y = mouseY0 + dragOffSetY;
    }

    lastMouseX = mouseX;
    lastMouseY = mouseY;
}

void mouse_button_callback (GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS && windowWidth > 0 && windowHeight > 0)
        {
            float dX = (2.0f * mouseX / windowWidth) - 1.0f;
            float dY = 1.0f - (2.0f * mouseY / windowHeight);

            dX *= (float)windowWidth / windowHeight;

            dragOffSetX = X - dX;
            dragOffSetY = Y - dY;

            isDragging = true;
            t = 0;
        }
        else if (action == GLFW_RELEASE)
        {
            isDragging = false;
        }
    }
}