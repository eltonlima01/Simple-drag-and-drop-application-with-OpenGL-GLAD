#ifndef HEADERS_H
#define HEADERS_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "shaders.h"
#include "utils.cpp"

void framebuffer_size_callback (GLFWwindow *window, int width, int height);
void cursor_position_callback (GLFWwindow *window, double xPos, double yPos);
void mouse_button_callback (GLFWwindow *window, int button, int action, int mods);

#endif