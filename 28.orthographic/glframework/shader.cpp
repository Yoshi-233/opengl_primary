//
// Created by nio on 24-8-21.
//
#include "shader.hpp"
#include <string>
#include <fstream>
#include <sstream>

Shader *shader = nullptr;

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
        // code
        std::string vertexCode;
        std::string fragmentCode;
        // for read files
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // 设置监听异常, 读取失败或文件损坏
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);

                std::stringstream vShaderStream, fShaderStream;
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();

                vShaderFile.close();
                fShaderFile.close();

                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
        } catch (std::ifstream::failure &e) {
                ERROR("shader file error: {}.\n", e.what());
        }

        this->setProgram(vertexCode, fragmentCode);
}

Shader::~Shader()
= default;

void Shader::begin() const
{
        GL_CHECK_ERR(glUseProgram(this->mProgram));
}

void Shader::end()
{
        GL_CHECK_ERR(glUseProgram(0));
}

void Shader::setProgram(std::string &vertexCode, std::string &fragmentCode)
{
        const char *vertexShaderSource = vertexCode.c_str();
        const char *fragmentShaderSource = fragmentCode.c_str();
        /* create shader */
        GLuint vertexShader, fragmentShader;
        vertexShader = GL_CHECK_ERR(glCreateShader(GL_VERTEX_SHADER));
        fragmentShader = GL_CHECK_ERR(glCreateShader(GL_FRAGMENT_SHADER));

        /* input shader code */
        GL_CHECK_ERR(glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr));
        GL_CHECK_ERR(glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr));

        /* compile */
        glCompileShader(vertexShader);
        checkShaderErrors(vertexShader, "COMPILE");
        glCompileShader(fragmentShader);
        checkShaderErrors(fragmentShader, "COMPILE");

        /* link */
        this->mProgram = glCreateProgram();
        glAttachShader(this->mProgram, vertexShader);
        glAttachShader(this->mProgram, fragmentShader);
        glLinkProgram(this->mProgram);
        checkShaderErrors(this->mProgram, "LINK");

        /* clear code */
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
}

void Shader::checkShaderErrors(GLuint target, std::string &&type) const
{
        int success = 0;
        char infoLog[1024];
        if (type == "COMPILE") {
                glGetShaderiv(target, GL_COMPILE_STATUS, &success);
                if (!success) {
                        glGetShaderInfoLog(target, 1024, nullptr, infoLog);
                        ERROR(infoLog);
                }
        } else if (type == "LINK") {
                glGetProgramiv(this->mProgram, GL_LINK_STATUS, &success);
                if (!success) {
                        glGetProgramInfoLog(this->mProgram, 1024, nullptr, infoLog);
                        ERROR(infoLog);
                }
        } else {
                ERROR("type({}) error!", type.c_str());
        }
}

void Shader::setFloat(const std::string &name, float &&value) const
{
        GLint location = GL_CHECK_ERR(glGetUniformLocation(this->mProgram, name.c_str()));

        GL_CHECK_ERR(glUniform1f(location, value));
}

void Shader::setVectorFloat(const std::string &name, const GLfloat *array) const
{
        GLint location = GL_CHECK_ERR(glGetUniformLocation(this->mProgram, name.c_str()));

        GL_CHECK_ERR(glUniform3fv(location, 1, (const GLfloat *) array));
}

void Shader::setVectorFloat(const std::string &name, float &&x, float &&y, float &&z) const
{
        GLint location = GL_CHECK_ERR(glGetUniformLocation(this->mProgram, name.c_str()));

        GL_CHECK_ERR(glUniform3f(location, x, y, z));
}

void Shader::setInt(const std::string &name, int &&value) const
{
        GLint location = GL_CHECK_ERR(glGetUniformLocation(this->mProgram, name.c_str()));

        GL_CHECK_ERR(glUniform1i(location, value));
}

