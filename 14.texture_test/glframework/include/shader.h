//
// Created by nio on 24-8-21.
//

#ifndef GLFW_TEST_SHADER_H
#define GLFW_TEST_SHADER_H

#include "core.h"
#include <string>
#include <vector>

class Shader;

extern Shader *shader;

class Shader {
public:
        explicit Shader(const char *vertexPath, const char *fragmentPath);

        ~Shader();

        void begin() const; // 开始使用当前的shader
        static void end(); // 结束使用当前的shader

        void setFloat(const std::string &name, float &&value) const;
        void setInt(const std::string &name, int &&value) const;
        void setVectorFloat(const std::string &name, float &&x, float &&y, float &&z) const;
        void setVectorFloat(const std::string &name, const GLfloat *array) const;

private:
        // COMPILE LINK
        void checkShaderErrors(GLuint target, std::string &&type) const;

private:
        GLuint mProgram{0};

        void setProgram(std::string &vertexShaderSource, std::string &fragmentShaderSource);
};

#endif //GLFW_TEST_SHADER_H
