//
// Created by Shaozheming on 2024/8/18.
//

#ifndef GLFW_TEST_APPLICATION_H
#define GLFW_TEST_APPLICATION_H

#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include "common.h"

#define APP Application::getInstance()

class GLFWwindow;

using ResizeCallback = void (*)(GLFWwindow *, int, int);
using KeyCallback = void (*)(GLFWwindow *, int, int, int, int);

class Application
{
public:
        ~Application();

        static Application &getInstance();

        /* 成员函数setter和getter */
        [[nodiscard]] unsigned int getWidth() const; // [[nodiscard]] 提示编译器不能忽略返回值
        [[nodiscard]] unsigned int getHeight() const;

        [[nodiscard]] const std::string &getTitle() const;

        /* 窗口相关函数 */
        bool init(const u32 &&width, const u32 &&height, const std::string &&title);

        [[maybe_unused]] bool update();

        void close();

        /* 回调函数 */
        void setResizeCallback(ResizeCallback callback)
        { mResizeCallback = callback; }
        void setKeyCallback(KeyCallback callback)
        { mKeyCallback = callback; }

        static void test();

private:
        /* 初始化成员变量 */
        static std::unique_ptr<Application> mInstance;
        static std::once_flag mOnceFlag;

        /* openlGL窗口相关属性 */
        static std::mutex mWindowMutex;
        bool mInit{false};
        u32 mWidth{0};
        u32 mHeight{0};
        std::string mTitle{"OpenGL Window"};
        GLFWwindow *mWindow{nullptr};

        /* 回调函数 */
        ResizeCallback mResizeCallback{nullptr};
        KeyCallback mKeyCallback{nullptr};

        // 这里必须是static的，否则是类内调用了
        static void resizeCallback(GLFWwindow *window, int width, int height);
        static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

private:
        /* 初始化函数 */
        Application();

        friend std::unique_ptr<Application> std::make_unique<Application>(); // 声明make_unique为友元函数
};

#endif //GLFW_TEST_APPLICATION_H
