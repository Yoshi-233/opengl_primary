#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float time;
out vec3 color;
out vec4 position;

uniform float speed;
void main()
{
        gl_Position = vec4(aPos.x + cos(time * speed) * 1 / 2, aPos.y + cos(time) * 1 / 2, aPos.z, 1.0f);
        position = gl_Position;

        color = aColor * (cos(time) + 1.0f) / 2.0f;
}