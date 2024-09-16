//
// Created by nio on 24-8-20.
//

#include "common.h"

std::shared_ptr<spdlog::logger> log_console;

void log_init()
{
        // 创建一个控制台记录器
        log_console = spdlog::stdout_color_mt("console");

        // 设置模式
        // %v - 实际的日志消息
        // %s - 源文件名
        // %# - 源行号
        // %! - 函数名
        // 更多格式化选项请查看spdlog文档
        log_console->set_pattern("[%H:%M:%S %z][%^%L%$][%s][%!:%#] %v");
        spdlog::set_default_logger(log_console);

        // 使用记录器
        SPDLOG_LOGGER_INFO(log_console, "Logger Init Success!");
}

void cpp_init()
{
        log_init();
}
