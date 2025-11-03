#version 330 core

in vec2 textureCoords;
in vec3 vertexColor;
out vec4 fragColor;

uniform sampler2D texture_diffuse;
uniform bool use_texture;

void main()
{
    vec4 vertexCol = vec4(vertexColor, 1.0);
    vec4 textureCol = texture(texture_diffuse, textureCoords);

    fragColor = use_texture ? texture(texture_diffuse, textureCoords) : vec4(vertexColor, 1.0);
}