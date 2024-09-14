//
// Created by nio on 24-8-21.
//

#ifndef GLFW_TEST_SHADER_H
#define GLFW_TEST_SHADER_H

#include "core.h"
#include "check_err.h"
#include "common.h"
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

        template<class mat_type>
        void setMatrix(const std::string &name, mat_type &value) const;

        template<class mat_type>
        void setMatrix(const std::string &name, mat_type &&value) const;

private:
        // COMPILE LINK
        void checkShaderErrors(GLuint target, std::string &&type) const;

private:
        GLuint mProgram{0};

        void setProgram(std::string &vertexShaderSource, std::string &fragmentShaderSource);
};

template<class mat_type>
void Shader::setMatrix(const std::string &name, mat_type &value) const
{
        GLint location = GL_CHECK_ERR(glGetUniformLocation(this->mProgram, name.c_str()));

        /*
         * 1. count:矩阵个数
         * 2. transpose:是否转置, glm是列存储的，所以不需要，如果数学库是行存储的需要
         * */
        if (std::is_same<mat_type, glm::mat4>::value) {
                GL_CHECK_ERR(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat3>::value) {
                GL_CHECK_ERR(glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat2>::value) {
                GL_CHECK_ERR(glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat4x2>::value) {
                GL_CHECK_ERR(glUniformMatrix4x2fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat4x3>::value) {
                GL_CHECK_ERR(glUniformMatrix4x3fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat3x2>::value) {
                GL_CHECK_ERR(glUniformMatrix3x2fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat3x4>::value) {
                GL_CHECK_ERR(glUniformMatrix3x4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat2x3>::value) {
                GL_CHECK_ERR(glUniformMatrix2x3fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat2x4>::value) {
                GL_CHECK_ERR(glUniformMatrix2x4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else {
                ERROR("type error!");
        }
}

template<class mat_type>
void Shader::setMatrix(const std::string &name, mat_type &&value) const
{
        GLint location = GL_CHECK_ERR(glGetUniformLocation(this->mProgram, name.c_str()));

        /*
         * 1. count:矩阵个数
         * 2. transpose:是否转置, glm是列存储的，所以不需要，如果数学库是行存储的需要
         * */
        if (std::is_same<mat_type, glm::mat4>::value) {
                GL_CHECK_ERR(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat3>::value) {
                GL_CHECK_ERR(glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat2>::value) {
                GL_CHECK_ERR(glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat4x2>::value) {
                GL_CHECK_ERR(glUniformMatrix4x2fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat4x3>::value) {
                GL_CHECK_ERR(glUniformMatrix4x3fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat3x2>::value) {
                GL_CHECK_ERR(glUniformMatrix3x2fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat3x4>::value) {
                GL_CHECK_ERR(glUniformMatrix3x4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat2x3>::value) {
                GL_CHECK_ERR(glUniformMatrix2x3fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else if (std::is_same<mat_type, glm::mat2x4>::value) {
                GL_CHECK_ERR(glUniformMatrix2x4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
        } else {
                ERROR("type error!");
        }
}


#endif //GLFW_TEST_SHADER_H
