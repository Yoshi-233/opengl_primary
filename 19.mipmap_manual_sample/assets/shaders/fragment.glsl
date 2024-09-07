#version 410 core
out vec4 fragColor;

uniform sampler2D grassSampler;
uniform sampler2D landSampler;
uniform sampler2D noiseSampler;
in vec3 color;
in vec2 uv;

uniform float width;
uniform float height;
void main()
{
        // 获取具体位置
        vec2 location = uv * vec2(width, height);
        // 获取纹素变化量
        vec2 dx = dFdx(location);
        vec2 dy = dFdy(location);
        // 计算最大的deta值
        float maxDelta = sqrt(max(dot(dx, dx), dot(dy, dy)));
        float L = log2(maxDelta);
        // 计算mipmap级别
        float level = max(int(L + 0.5), 0);

        vec4 grassColor = textureLod(grassSampler, uv, level);
        vec4 landColor = textureLod(landSampler, uv, level);
        vec4 noiseColor = textureLod(noiseSampler, uv, level);
        float weight = noiseColor.r;

        // vec4 finalColor = grassColor * weight + landColor * (1.0 - weight);\
        // weight对应landColor的权重
        vec4 finalColor = mix(grassColor, landColor, weight);
        // 有些情况下透明值不一定是1.0
        fragColor = vec4(finalColor.rgb, 1.0);
}