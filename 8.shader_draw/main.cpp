#include <glad/glad.h>  // 必须为首句
#include <GLFW/glfw3.h>
#include <iostream>
#include "Application/include/Application.h"
#include "common/include/check_err.h"
#include "common/include/common.h"

GLuint vao = 0, program = 0;

// 窗口大小改变回调函数
void OnResize(GLFWwindow *window, int width, int height)
{
        GL_CHECK_ERR(glViewport(0, 0, width, height));
}

/*
 * key_callback() 函数用于处理键盘事件
 * 参数：
 * GLFWwindow *window：当前窗口的句柄
 * int key：按下的键的键码
 * int scancode：按下的键的扫描码, 物理按键码, 有些键盘排布不一致，根据位置推算按键，一般不用
 * int action：键的动作，如按下或释放
 * int mode：当前窗口的输入模式， 如shift、ctrl等
 * */
void OnKeyBoard(GLFWwindow *window, int key, int scancode, int action, int mode)
{
        if ((key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) ||
            (key == GLFW_KEY_C && action == GLFW_RELEASE && mode == GLFW_MOD_CONTROL)) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
}

void prepareSingleBuffer()
{
        float position[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f,  0.0f
        };

        float color[] = {
                1.0f, 0.0f, 0.0f,
                0.5f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f
        };
        GLuint posVbo = 0, colorVbo = 0;
        GL_CHECK_ERR(glGenBuffers(1, &posVbo));
        GL_CHECK_ERR(glGenBuffers(1, &colorVbo));


        // GL_ARRAY_BUFFER current vbo
        GL_CHECK_ERR(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
        GL_CHECK_ERR(glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW));

        GL_CHECK_ERR(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
        GL_CHECK_ERR(glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW));

        /* vao */
        GLuint vao = 0;
        GL_CHECK_ERR(glGenVertexArrays(1, &vao));
        GL_CHECK_ERR(glBindVertexArray(vao));

        // must use bind
        GL_CHECK_ERR(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
        GL_CHECK_ERR(glEnableVertexAttribArray(0)); // enable vao 0th attr
        GL_CHECK_ERR(glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                                3 * sizeof(float), (void *)0));
        GL_CHECK_ERR(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
        GL_CHECK_ERR(glEnableVertexAttribArray(1)); // enable vao 0th attr
        GL_CHECK_ERR(glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                                                3 * sizeof(float), (void *)0));

        // unbind
        GL_CHECK_ERR(glBindVertexArray(0));
        GL_CHECK_ERR(glDeleteVertexArrays(1, &vao));

        GL_CHECK_ERR(glDeleteBuffers(1, &posVbo));
        GL_CHECK_ERR(glDeleteBuffers(1, &colorVbo));

}

void prepareInterleaveBuffer()
{
        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 0.5f, 1.0f, 0.0f,
                0.0f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f
        };

        GLuint vbo = 0;
        GL_CHECK_ERR(glGenBuffers(1, &vbo));

        // GL_ARRAY_BUFFER current vbo
        GL_CHECK_ERR(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GL_CHECK_ERR(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

        /* vao */
        GL_CHECK_ERR(glGenVertexArrays(1, &vao));
        GL_CHECK_ERR(glBindVertexArray(vao));

        // must use bind
        GL_CHECK_ERR(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GL_CHECK_ERR(glEnableVertexAttribArray(0)); // enable vao 0th attr
        GL_CHECK_ERR(glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                                6 * sizeof(float), (void *)0));
        GL_CHECK_ERR(glEnableVertexAttribArray(1)); // enable vao 1th attr color
        GL_CHECK_ERR(glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                                                6 * sizeof(float), (void *)(3 * sizeof(float))));

        // unbind
        GL_CHECK_ERR(glBindVertexArray(0));
//        GL_CHECK_ERR(glDeleteVertexArrays(1, &vao));
//
//        GL_CHECK_ERR(glDeleteBuffers(1, &vbo));

}

void prepareShader()
{
        const char* vertexShaderSource =
                "#version 460 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "void main()\n"
                "{\n"
                " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f); \n"
                "}\n\0";

        const char* fragmentShaderSource =
                "#version 460 core\n"
                "out vec4 fragColor;\n"
                "void main()\n"
                "{\n"
                " fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
                "}\n\0";

        /* create shader */
        GLuint vertexShader, fragmentShader;
        vertexShader = GL_CHECK_ERR(glCreateShader(GL_VERTEX_SHADER));
        fragmentShader = GL_CHECK_ERR(glCreateShader(GL_FRAGMENT_SHADER));

        /* input shader code */
        GL_CHECK_ERR(glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr));
        GL_CHECK_ERR(glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr));

        /* compile */
        int success = 0;
        char infoLog[1024];
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success) {
                glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
                ERROR(infoLog);
        }
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success) {
                glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLog);
                ERROR(infoLog);
        }

        /* link */
        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if(!success) {
                glGetProgramInfoLog(program, 1024, nullptr, infoLog);
                ERROR(infoLog);
        }

        /* clear code */
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
}

void render()
{
        // 清屏
        GL_CHECK_ERR(glClear(GL_COLOR_BUFFER_BIT));
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main()
{
        cpp_init();
        if (!APP.init(800, 600, "LearnOpenGL")) {
                ERROR( "Failed to initialize Application");
                return -1;
        }

        APP.setResizeCallback(OnResize);
        APP.setKeyCallback(OnKeyBoard);

        // opengl渲染的区域
        GL_CHECK_ERR(glViewport(0, 0, 800, 600));
        // 设置清屏颜色
        GL_CHECK_ERR(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

        prepareShader();
        prepareSingleBuffer();
        prepareInterleaveBuffer();

        while (APP.update()) {
                render();
                // 绘制代码
        }
        APP.close();
        return 0;
}