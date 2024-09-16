//
// Created by Shaozheming on 2024/9/16.
//

#ifndef GEOMETRY_GEOMETRY_H
#define GEOMETRY_GEOMETRY_H

#include "core.h"

class Geometry {
public:
        Geometry();

        ~Geometry();

        static Geometry *createBox(float size);

        static Geometry *createSphere(float radius);

        [[nodiscard]] GLuint getVao() const
        { return mVao; };

        [[nodiscard]] GLuint getPosVbo() const
        { return mPosVbo; };

        [[nodiscard]] GLuint getUvVbo() const
        { return mUvVbo; };

        [[nodiscard]] GLuint getEbo() const
        { return mEbo; };

        [[nodiscard]] int getIndicesCount() const
        { return mIndicesCount; };

public:
        GLuint mVao{0};
        GLuint mPosVbo{0};
        GLuint mUvVbo{0};
        GLuint mEbo{0};

        int mIndicesCount{0};

};

#endif //GEOMETRY_GEOMETRY_H
