//
// Created by Shaozheming on 2024/8/17.
//

#ifndef GLFW_TEST_CHECK_ERR_H
#define GLFW_TEST_CHECK_ERR_H

#include <iostream>

#ifdef DEBUG_MODE
#define GL_CHECK_ERR(func) func; \
error_check()
#else
#define GL_CHECK_ERR(func) func
#endif

void error_check();

#endif //GLFW_TEST_CHECK_ERR_H
