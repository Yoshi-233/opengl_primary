#include "glframework/include/core.h"
#include "glframework/include/shader.h"
#include "application/Application.h"
#include "common/include/check_err.h"
#include "common/include/common.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

/*
 * 1. load image
 * 2. create texture object
 * 3. bind texture
 * */

GLuint vao = 0;
GLuint texture = 0;

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
                2.0f, 0.0f,
                0.0f, 1.0f,
                3.0f, 1.0f
        };

        u32 indices[] = {
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
        s32 width, height, channels;
        /* 1. 读取图片时要反转y轴 */
        stbi_set_flip_vertically_on_load(true);
        u8 *data = stbi_load("assets/textures/dog_1.jpg",
                             &width, &height, &channels, STBI_rgb_alpha);
        INFO("width: {}, height: {}, channels: {}.\n", width, height, channels);

        /* 2. 生成1个纹理对象 */
        glGenTextures(1, &texture);
        /* 激活纹理单元 */
        glActiveTexture(GL_TEXTURE0); // 激活0号纹理
        /* 绑定纹理对象，为2D纹理， 如果后续再绑定别的纹理会替换当前纹理 */
        glBindTexture(GL_TEXTURE_2D, texture);

        /* 3.传输纹理数据到gpu, 该行为会开辟显存 */
        // param0: 2d texture
        // param1: level = 0表示单层纹理
        // param2: format, gpu上的图片格式
        // param7: 传入图片的数据格式
        // param8: 传入图片的数据格式的存储格式
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        /* 4.释放数据， 传输完纹理数据后需要释放data */
        stbi_image_free(data);

        /* 5.设置纹理过滤方式 */
        // 正常情况下，当需要的像素大于原始image, GL_LINEAR, else GL_NEAREST
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        /* 6.设置纹理wraping方式 */
        // GL_TEXTURE_WRAP_S = u, GL_TEXTURE_WRAP_T = v
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // 注意这里不能使用glBindTexture(GL_TEXTURE_2D, 0);解绑
}

void render()
{
        // 清屏
        GL_CHECK_ERR(glClear(GL_COLOR_BUFFER_BIT));
        shader->begin();

        // 设置sampler采样第0号纹理，注意这里默认是0
        shader->setInt("sampler", 0);
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

        while (APP.update()) {
                render();
                // 绘制代码
        }
        APP.close();
        return 0;
}