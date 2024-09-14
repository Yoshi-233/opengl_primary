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
        Texture(const std::string &path, unsigned int unit);

        ~Texture();

public:
        void bind() const;

        [[nodiscard]] int getWidth() const;

        [[nodiscard]] int getHeight() const;

private:
        GLuint mTexture{0};
        int mWidth{0};
        int mHeight{0};
        unsigned int mUnit{0}; // GL_TEXTURE0 + mUnit 表示绑定的纹理单元
};

#endif //TEXTURE_TEXTURE_H
