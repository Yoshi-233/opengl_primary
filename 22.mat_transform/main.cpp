#include "glframework/include/core.h"
#include "glframework/include/shader.h"
#include "glframework/include/texture.h"
#include "application/Application.h"
#include "common/include/check_err.h"
#include "common/include/common.h"

/*
 * 1. 生成mipmap各个级别
 * 2. 修改vs随着时间变小
 * */

GLuint vao = 0;
std::shared_ptr<Texture> grassTexture;
std::shared_ptr<Texture> landTexture;
std::shared_ptr<Texture> noiseTexture;
std::shared_ptr<Texture> dogTexture;
glm::mat4 transform;

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
                -0.5f, 0.5f, 0.0f,
                0.5f, 0.5f, 0.0f
        };

        float colors[] = {
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f,
                0.5f, 0.5f, 0.5f
        };

        float uvs[] = {
                0.0f, 0.0f,
                1.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 1.0f
        };

        glm::u32 indices[] = {
                0, 1, 2,
                2, 1, 3
        };

        /* create vbo */
        GLuint posVbo, colorVbo, uvVbo;
        glGenBuffers(1, &posVbo);
        glBindBuffer(GL_ARRAY_BUFFER, posVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
        glGenBuffers(1, &colorVbo);
        glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        glGenBuffers(1, &uvVbo);
        glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

        /* create ebo */
        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        /* create vao */
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        /* bind vbo/ebo */
        glBindBuffer(GL_ARRAY_BUFFER, posVbo);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *) 0);
        glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *) 0);
        glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *) 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        glBindVertexArray(0);
}

void prepareShader()
{
        shader = new Shader("assets/shaders/vertex.glsl",
                            "assets/shaders/fragment.glsl");
}

void prepareTexture()
{
        grassTexture = std::make_shared<Texture>("assets/textures/grass.jpg", 0);
        landTexture = std::make_shared<Texture>("assets/textures/land.jpg", 1);
        noiseTexture = std::make_shared<Texture>("assets/textures/noise.jpg", 2);
        dogTexture = std::make_shared<Texture>("assets/textures/dog_1.jpg", 3);
}

void doRotationTransform()
{
        /* 构建一个旋转矩阵，绕Z轴旋转45 */
        // angle必须是float, 45.0默认是double
        // angle接收的不是角度，是弧度
        transform = glm::rotate(glm::mat4(1.0), glm::radians(45.0f),
                                glm::vec3(0.0, 0.0, 1.0)); // 用于生成旋转矩阵
}

void doTranslationTransform()
{
        /* 构建一个平移矩阵 */
        transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
}

void doScaleTransform()
{
        /* 构建一个缩放矩阵 */
        transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));
}

void doTransform()
{
        glm::mat4 rotateTransform = glm::rotate(glm::mat4(1.0f),
                                                glm::radians(45.0f),
                                                glm::vec3(0.0f, 0.0f, 1.0f)); // 用于生成旋转矩阵
        glm::mat4 translateTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
        // 旋转平移和平移旋转效果不一样
        transform = translateTransform * rotateTransform;
}

float angle;

void doRotate()
{
        angle += 2.0f;
        transform = glm::rotate(glm::mat4(1.0f),
                                glm::radians(angle),
                                glm::vec3(0.0f, 0.0f, 1.0f)); // 用于生成旋转矩阵
}

void render()
{
        // 清屏
        GL_CHECK_ERR(glClear(GL_COLOR_BUFFER_BIT));
        shader->begin();

        // 设置sampler采样第0号纹理，注意这里默认是0
        shader->setInt("grassSampler", 0);
        shader->setInt("landSampler", 1);
        shader->setInt("noiseSampler", 2);
        shader->setInt("dogSampler", 3);
        shader->setMatrix<decltype(transform)>("transform", transform);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        // 这里最好解绑，这样误操作就不会影响当前vao
        Shader::end();
}

int main()
{
        cpp_init();
        if (!APP.init(800, 600, "LearnOpenGL")) {
                ERROR("Failed to initialize Application");
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
        prepareTexture();

        // doRotationTransform();
        // doTranslationTransform();
        // doScaleTransform();
        // doTransform();

        while (APP.update()) {
                // 注意：每次都是从头旋转
                doRotate();
                render();
                // 绘制代码
        }
        APP.close();
        return 0;
}