#version 410 core
out vec4 fragColor;
in vec3 color;
// uniform 可以重名，这样所有glsl共用
//uniform float color_time;
uniform float time;
void main()
{
        float intensity = (sin(time) + 1.0f) / 2.0f;
        fragColor = vec4(vec3(intensity) + color, 1.0f);
}