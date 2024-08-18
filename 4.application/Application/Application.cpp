//
// Created by Shaozheming on 2024/8/18.
//

#include "include/Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "check_err.h"

std::unique_ptr<Application> Application::mInstance = nullptr;
std::once_flag Application::mOnceFlag;
std::mutex Application::mWindowMutex;

std::unique_ptr<Application> Application::getInstance()
{
        std::call_once(mOnceFlag, []() {
                mInstance = std::unique_ptr<Application>(new Application());
        });
        return std::move(mInstance);
}

void Application::test()
{
        std::cout << "Application::test()" << std::endl;
}

unsigned int Application::getWidth() const
{
        return mWidth;
}

unsigned int Application::getHeight() const
{
        return mHeight;
}

const std::string &Application::getTitle() const
{
        return mTitle;
}

bool Application::init(const u32 &&width, const u32 &&height, const std::string &&title)
{
        std::lock_guard<std::mutex> lock(mWindowMutex);
        if (this->mInit) {
                std::cout << "Application already running" << std::endl;
                return false;
        }
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        this->mWindow = glfwCreateWindow((int) width, (int) height, title.c_str(),
                                         nullptr, nullptr);
        if (this->mWindow == nullptr) {
                std::cout << "Failed to create GLFW window" << std::endl;

                return false;
        }
        glfwMakeContextCurrent(this->mWindow);

        this->mWidth = width;
        this->mHeight = height;
        this->mTitle = title;
        this->mInit = true;

        // 加载glad 用来加载opengl函数
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                std::cout << "Failed to initialize GLAD" << std::endl;
                this->close();
                return false;
        }

        // opengl渲染的区域
        GL_CHECK_ERR(glViewport(0, 0, width, height));
        // 设置清屏颜色
        GL_CHECK_ERR(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

        return true;
}

[[maybe_unused]] bool Application::update()
{
        std::lock_guard<std::mutex> lock(mWindowMutex);
        if (!this->mInit) {
                std::cout << "Application not running" << std::endl;
                return false;
        }

        if (glfwWindowShouldClose(this->mWindow)) {
                return false;
        }

        glfwPollEvents();
        // 双缓冲绘制，交替绘制缓冲区
        glfwSwapBuffers(this->mWindow);
        return true;
}

void Application::close()
{
        std::lock_guard<std::mutex> lock(mWindowMutex);
        if (!this->mInit) {
                std::cout << "Application not running" << std::endl;
                return;
        }
        this->mWidth = 0;
        this->mHeight = 0;
        this->mTitle = "";
        this->mInit = false;
        glfwTerminate();
}

Application::~Application()
= default;

Application::Application()
= default;
