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
        Texture();
        ~Texture();
private:
        GLuint mTexture{0};

};

#endif //TEXTURE_TEXTURE_H
