#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

out vec3 color;
out vec2 uv;

uniform mat4 transform;
uniform mat4 viewMatrix;

void main()
{
        // aPos不允许更改
        // transform * vec4(aPos, 1.0)是自己旋转
        // viewMatrix是摄像机
        gl_Position = viewMatrix * transform * vec4(aPos, 1.0);
        color = aColor;
        uv = aUV;
}