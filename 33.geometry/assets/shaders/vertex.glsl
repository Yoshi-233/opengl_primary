#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 uv;

uniform mat4 transform;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
        // aPos不允许更改
        // transform * vec4(aPos, 1.0)是自己旋转
        // viewMatrix是摄像机
        // projectionMatrix是投影矩阵
        gl_Position = projectionMatrix * viewMatrix * transform * vec4(aPos, 1.0);
        uv = aUV;
}