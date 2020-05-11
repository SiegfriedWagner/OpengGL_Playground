#version 330 core
out vec4 FragColor;
in vec3 Position;
in vec3 Color;
void main()
{
    float mean = (Color.r + Color.g + Color.b) / 3.0;
    FragColor = vec4(mean, mean, mean, 1.0f);
}