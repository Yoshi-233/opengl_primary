//
// Created by Shaozheming on 2024/9/3.
//
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

Texture::Texture(const std::string &path, unsigned int unit)
{
        this->mUnit = unit;
        int channels;
        /* 1. 读取图片时要反转y轴 */
        stbi_set_flip_vertically_on_load(true);
        glm::u8 *data = stbi_load(path.c_str(),
                                  &this->mWidth, &this->mHeight, &channels, STBI_rgb_alpha);


        /* 2. 生成1个纹理对象 */
        glGenTextures(1, &this->mTexture);
        /* 激活纹理单元 */
        glActiveTexture(GL_TEXTURE0 + this->mUnit); // 激活0号纹理
        /* 绑定纹理对象，为2D纹理， 如果后续再绑定别的纹理会替换当前纹理 */
        glBindTexture(GL_TEXTURE_2D, this->mTexture);

        /* 3.传输纹理数据到gpu, 该行为会开辟显存 */
        // param0: 2d texture
        // param1: level = 0表示单层纹理，mipmap等级
        // param2: format, gpu上的图片格式
        // param7: 传入图片的数据格式
        // param8: 传入图片的数据格式的存储格式
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->mWidth, this->mHeight,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        /* 4.释放数据， 传输完纹理数据后需要释放data */
        stbi_image_free(data);

        /* 5.设置纹理过滤方式 */
        // 正常情况下，当需要的像素大于原始image, GL_LINEAR, else GL_NEAREST
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 这里如果想用mipmap, 则需要设置GL_TEXTURE_MIN_FILTER为GL_LINEAR_MIPMAP_LINEAR, 否则为GL_NEAREST
        // GL_LINEAR是在单个mipmap层级上进行线性插值，GL_NEAREST是在单个mipmap层级上进行最近邻插值
        // MIPMAP_LINEAR是在所有mipmap层级上进行线性插值
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

        /* 6.设置纹理wraping方式 */
        // GL_TEXTURE_WRAP_S = u, GL_TEXTURE_WRAP_T = v
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // 注意这里不能使用glBindTexture(GL_TEXTURE_2D, 0);解绑
}

Texture::~Texture()
{
        if (this->mTexture != 0) {
                glDeleteTextures(1, &this->mTexture);
        }
}

void Texture::bind() const
{
        /* 激活纹理单元, 这一步必须, 如果其他纹理单元激活会不小心绑定错误 */
        glActiveTexture(GL_TEXTURE0 + this->mUnit);
        /* 绑定纹理对象，为2D纹理， 如果后续再绑定别的纹理会替换当前纹理 */
        glBindTexture(GL_TEXTURE_2D, this->mTexture);
}

int Texture::getWidth() const
{
        return this->mWidth;
}

int Texture::getHeight() const
{
        return this->mHeight;
}



