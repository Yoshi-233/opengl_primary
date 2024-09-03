#version 410 core
out vec4 fragColor;

uniform sampler2D sampler;
in vec3 color;
in vec2 uv;

void main()
{
        fragColor = texture(sampler, uv);
}