#ifndef SHADERS_H
#define SHADERS_H

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

#endif