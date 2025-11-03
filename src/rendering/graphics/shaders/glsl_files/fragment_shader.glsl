#version 330 core

in vec2 TexCoords;
in vec3 vertexColor;
out vec4 FragColor;

uniform sampler2D texture_diffuse;

// todo: fix hacky fragment code

void main()
{
    vec4 vertexCol = vec4(vertexColor, 1.0);
    vec4 texCol = texture(texture_diffuse, TexCoords);

    if(texCol.rgb == vec3(0.0))
        FragColor = vertexCol;
    else
        FragColor = mix(vertexCol, texCol, 1.0);
}