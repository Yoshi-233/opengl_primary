#version 410 core
out vec4 fragColor;

uniform sampler2D grassSampler;
uniform sampler2D landSampler;
uniform sampler2D noiseSampler;
in vec3 color;
in vec2 uv;

void main()
{
        vec4 grassColor = texture(grassSampler, uv);
        vec4 landColor = texture(landSampler, uv);
        vec4 noiseColor = texture(noiseSampler, uv);
        float weight = noiseColor.r;

        // vec4 finalColor = grassColor * weight + landColor * (1.0 - weight);\
        // weight对应landColor的权重
        vec4 finalColor = mix(grassColor, landColor, weight);
        // 有些情况下透明值不一定是1.0
        fragColor = vec4(finalColor.rgb, 1.0);
}