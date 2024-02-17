#version 330 core

// Coordinates Layout
layout (location = 0) in vec3 aPos;

// Colors Layout
layout (location = 1) in vec3 aColor;

// Send color to Fragment Shader
out vec3 color;

uniform float scale;

void main()
{

   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);

   // Assigns colors from Vertex
   color = aColor;

}