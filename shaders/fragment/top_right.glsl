#version 330 core
uniform float screenWidth = 1920;
uniform float screenHeight = 1080;
out vec4 FragColor;
in vec3 Color;
void main()
{
    if(gl_FragCoord.x / screenWidth > 0.5 && gl_FragCoord.y / screenHeight > 0.5)
        FragColor = vec4(vec3(1.0, 1.0, 1.0) - Color, 1.0);
    else
        FragColor = vec4(Color, 1.0f);
}