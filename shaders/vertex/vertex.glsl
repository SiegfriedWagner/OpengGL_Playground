#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

const mat4 matrixUnitary = mat4(1.0);
uniform mat4 matrixWorld = matrixUnitary;
uniform mat4 matrixView = matrixUnitary;
uniform mat4 matrixProjection = matrixUnitary; 

mat4 matrixMVP = matrixProjection * matrixView * matrixWorld;
out vec4 Position;
out vec4 Color;
void main()
{
   Position = vec4(aPos, 1.0);
   Color = vec4(aColor, 1.0);
   gl_Position = matrixMVP * Position;
   Position = matrixWorld * Position;
}