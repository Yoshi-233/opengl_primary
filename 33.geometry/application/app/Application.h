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

using ResizeCallback = void (*)(int, int);
using KeyCallback = void (*)(int, int, int, int);
using MouseButtonCallback = void (*)(int, int, int);
using CursorPosCallback = void (*)(double, double);
using ScrollCallback = void (*)(double);

class Application {
public:
        ~Application();

        static Application &getInstance();

public:
        /* 成员函数setter和getter */
        [[nodiscard]] unsigned int getWidth() const; // [[nodiscard]] 提示编译器不能忽略返回值
        [[nodiscard]] unsigned int getHeight() const;
        [[nodiscard]] GLFWwindow *getWindow() const;

        [[nodiscard]] const std::string &getTitle() const;

        void getCursorPos(double *xpos, double *ypos) const;

public:
        /* 窗口相关函数 */
        bool init(const unsigned int &&width, const unsigned int &&height, const std::string &&title);

        [[maybe_unused]] bool update();

        void close();

public:
        /* 回调函数 */
        void setResizeCallback(ResizeCallback callback)
        { mResizeCallback = callback; }

        void setKeyCallback(KeyCallback callback)
        { mKeyCallback = callback; }

        void setMouseButtonCallback(MouseButtonCallback callback)
        { mMouseButtonCallback = callback; }

        void setCursorPosCallback(CursorPosCallback callback)
        { mCursorPosCallback = callback; }

        void setScrollCallback(ScrollCallback callback)
        { mScrollCallback = callback; }

        static void test();

private:
        /* 初始化成员变量 */
        static std::unique_ptr<Application> mInstance;
        static std::once_flag mOnceFlag;

        /* openlGL窗口相关属性 */
        static std::mutex mWindowMutex;
        bool mInit{false};
        unsigned int mWidth{0};
        unsigned int mHeight{0};
        std::string mTitle{"OpenGL Window"};
        GLFWwindow *mWindow{nullptr};

        /* 回调函数 */
        ResizeCallback mResizeCallback{nullptr};
        KeyCallback mKeyCallback{nullptr};
        MouseButtonCallback mMouseButtonCallback{nullptr};
        CursorPosCallback mCursorPosCallback{nullptr};
        ScrollCallback mScrollCallback{nullptr};

        // 这里必须是static的，否则是类内调用了
        static void resizeCallback(GLFWwindow *window, int width, int height);

        static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

        static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

        static void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);

        static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

private:
        /* 初始化函数 */
        Application();

        friend std::unique_ptr<Application> std::make_unique<Application>(); // 声明make_unique为友元函数
};

#endif //GLFW_TEST_APPLICATION_H
