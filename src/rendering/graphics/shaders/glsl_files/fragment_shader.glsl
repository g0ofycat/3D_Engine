#version 330 core

in vec2 TexCoords;
in vec3 vertexColor;
out vec4 FragColor;

uniform sampler2D texture_diffuse;
uniform bool useTexture;

void main()
{
    vec4 baseColor = vec4(vertexColor, 1.0);

    if(useTexture)
        baseColor *= texture(texture_diffuse, TexCoords);

    FragColor = baseColor;
}