#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

out vec3 color;
out vec2 uv;

uniform float time;

void main()
{
        gl_Position = vec4(aPos, 1.0);
        color = aColor;

        float detlaU = time * 0.3;
        uv = aUV + vec2(detlaU, 0);
}