//
// Created by Shaozheming on 2024/8/18.
//

#ifndef GLFW_TEST_COMMON_H
#define GLFW_TEST_COMMON_H

#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include <glm/fwd.hpp>

extern std::shared_ptr<spdlog::logger> log_console;
#define WARN(...) SPDLOG_LOGGER_WARN(log_console, __VA_ARGS__)
#define CRITICAL(...) SPDLOG_LOGGER_CRITICAL(log_console, __VA_ARGS__)
#define DBG(...) SPDLOG_LOGGER_DEBUG(log_console, __VA_ARGS__)
#define INFO(...) SPDLOG_LOGGER_INFO(log_console, __VA_ARGS__)
#define ERROR(...) SPDLOG_LOGGER_ERROR(log_console, __VA_ARGS__)

void cpp_init();

#endif //GLFW_TEST_COMMON_H
