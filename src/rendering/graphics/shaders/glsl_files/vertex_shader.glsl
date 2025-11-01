#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 objPos;

uniform vec3 objScale;

void main()
{
    vec3 scaledPos = objScale * aPos;
    vec3 worldPos = objPos + scaledPos;
    gl_Position = projection * view * model * vec4(worldPos, 1.0);
    vertexColor = aColor;
}