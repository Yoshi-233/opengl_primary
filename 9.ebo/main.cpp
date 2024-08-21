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

void prepareVao()
{
        float positions[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f,
                0.5f, 0.5f, 0.0f
        };

        u32 indices[] = {
                0, 1, 2,
                2, 1, 3
        };

        /* create vbo */
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

        /* create ebo */
        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        /* create vao */
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        /* bind vbo/ebo */
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        glBindVertexArray(0);
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

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        // 这里最好解绑，这样误操作就不会影响当前vao
        glBindVertexArray(0);
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

        prepareVao();
        prepareShader();

        while (APP.update()) {
                render();
                // 绘制代码
        }
        APP.close();
        return 0;
}