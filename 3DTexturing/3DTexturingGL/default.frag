#version 330 core

// RGBA Output
out vec4 FragColor;

// Input color from Vertex Shader
in vec3 color;

// Input texture from Vertex
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, texCoord);
}

