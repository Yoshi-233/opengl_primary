//
// Created by Shaozheming on 2024/8/18.
//

#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "check_err.h"

std::unique_ptr<Application> Application::mInstance = nullptr;
std::once_flag Application::mOnceFlag;
std::mutex Application::mWindowMutex;

Application &Application::getInstance()
{
        std::call_once(mOnceFlag, []() {
                mInstance = std::unique_ptr<Application>(new Application());
        });
        return *mInstance;
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

bool Application::init(const unsigned int &&width, const unsigned int &&height, const std::string &&title)
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
        glfwSetWindowUserPointer(this->mWindow, this);

        glfwSetFramebufferSizeCallback(this->mWindow, resizeCallback);
        glfwSetKeyCallback(this->mWindow, keyCallback);

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

void Application::resizeCallback(GLFWwindow *window, int width, int height)
{
        auto self = static_cast<Application *>(glfwGetWindowUserPointer(window));
        if (self == nullptr) {
                return;
        }

        self->mWidth = width;
        self->mHeight = height;

        if (self->mResizeCallback) {
                self->mResizeCallback(window, width, height);
        }
}

void Application::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
        auto self = static_cast<Application *>(glfwGetWindowUserPointer(window));
        if (self == nullptr) {
                return;
        }

        if (self->mKeyCallback) {
                self->mKeyCallback(window, key, scancode, action, mods);
        }
}

Application::~Application()
= default;

Application::Application()
= default;
