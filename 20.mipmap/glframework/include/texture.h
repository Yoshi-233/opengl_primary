//
// Created by Shaozheming on 2024/9/3.
//

#ifndef TEXTURE_TEXTURE_H
#define TEXTURE_TEXTURE_H

#include "check_err.h"
#include "common.h"
#include "core.h"

class Texture {
public:
        Texture(const std::string& path, u32 unit);

        ~Texture();
public:
        void bind() const;
        [[nodiscard]] s32 getWidth() const;
        [[nodiscard]] s32 getHeight() const;

private:
        GLuint mTexture{0};
        s32 mWidth{0};
        s32 mHeight{0};
        u32 mUnit{0}; // GL_TEXTURE0 + mUnit 表示绑定的纹理单元
};

#endif //TEXTURE_TEXTURE_H
