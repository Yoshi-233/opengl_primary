//
// Created by Shaozheming on 2024/8/17.
//
#include <iostream>
#include <cassert>
#include <glad/glad.h>  // 必须为首句
#include "common.h"

// 错误检查
void error_check()
{
        GLenum error = glGetError();
        std::string error_description;
        if (error != GL_NO_ERROR) {
                switch (error) {
                        case GL_INVALID_ENUM:
                                error_description = "GL_INVALID_ENUM";
                                break;
                        case GL_INVALID_VALUE:
                                error_description = "GL_INVALID_VALUE";
                                break;
                        case GL_INVALID_OPERATION:
                                error_description = "GL_INVALID_OPERATION";
                                break;
                        case GL_STACK_OVERFLOW:
                                error_description = "GL_STACK_OVERFLOW";
                                break;
                        case GL_STACK_UNDERFLOW:
                                error_description = "GL_STACK_UNDERFLOW";
                                break;
                        case GL_OUT_OF_MEMORY:
                                error_description = "GL_OUT_OF_MEMORY";
                                break;
                        case GL_INVALID_FRAMEBUFFER_OPERATION:
                                error_description = "GL_INVALID_FRAMEBUFFER_OPERATION";
                                break;
                        default:
                                error_description = "Unknown Error";
                                break;
                }
                ERROR("OpenGL Error: {}", error_description);
                assert(false);
        }
}
