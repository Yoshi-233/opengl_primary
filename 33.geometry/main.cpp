#include "glframework/include/core.h"
#include "glframework/include/shader.hpp"
#include "glframework/include/texture.h"
#include "glframework/include/geometry.h"
#include "application/app/Application.h"
#include "common/include/check_err.h"
#include "common/include/common.h"

#include "application/camera/include/camera.h"
#include "application/camera/include/orthographicCamera.h"
#include "application/camera/include/perspectiveCamera.h"
#include "application/camera/include/trackballCameraController.h"
#include "application/camera/include/gameCameraController.h"


/*
 * 1. 生成mipmap各个级别
 * 2. 修改vs随着时间变小
 * */

Geometry *geometry;
std::shared_ptr<Texture> grassTexture;
std::shared_ptr<Texture> landTexture;
std::shared_ptr<Texture> noiseTexture;
std::shared_ptr<Texture> dogTexture;
std::shared_ptr<Texture> testLandTexture;
glm::mat4 transform{1.0f};

std::unique_ptr<Camera> camera;
std::shared_ptr<CameraControl> cameraControl;

// 窗口大小改变回调函数
void OnResize(int width, int height)
{
        GL_CHECK_ERR(glViewport(0, 0, width, height));
}

void OnKeyBoard(int key, int scancode, int action, int mode)
{
        cameraControl->onKey(key, action, mode);
}

void OnMouse(int button, int action, int mods)
{
        auto xPos = std::make_shared<double>();
        auto yPos = std::make_shared<double>();
        APP.getCursorPos(xPos.get(), yPos.get());

        cameraControl->onMouse(button, action, *xPos, *yPos);
}

void OnCursorPos(double xpos, double ypos)
{
        cameraControl->onCursor(xpos, ypos);
}

void OnScroll(double yoffset)
{
        cameraControl->onScroll(static_cast<float>(yoffset));
}


void prepareVao()
{
        geometry = Geometry::createSphere(6.0f);
        INFO("{}", geometry->getIndicesCount());
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
        testLandTexture = std::make_shared<Texture>("assets/textures/land.jpg", 3);
}

void prepareCamera()
{
        camera = std::make_unique<PerspectiveCamera>(60.0f,
                                                     (float) APP.getWidth() / (float) APP.getHeight(),
                                                     0.1f, 1000.f);

        // // 注意必须包含相机和图像
        // int size = 6.0f;
        // camera = std::make_unique<OrthographicCamera>(-size, size,
        //                                               -size, size,
        //                                               size, -size);

        cameraControl = std::make_shared<GameCameraController>();
        cameraControl->setCamera(camera.get());
        // 智能指针安全向下转型
        std::dynamic_pointer_cast<GameCameraController>(cameraControl)->setSpeed(0.5);
}

void prepareState()
{
        /* 设置opengl状态 */
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
}

void render()
{
        // 清屏
        GL_CHECK_ERR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        shader->begin();

        // 设置sampler采样第0号纹理，注意这里默认是0
        shader->setInt("grassSampler", 0);
        shader->setInt("landSampler", 1);
        shader->setInt("noiseSampler", 2);
        shader->setInt("dogSampler", 3);
        shader->setMatrix<decltype(transform)>("transform", transform);
        shader->setMatrix<decltype(camera->getViewMatrix())>("viewMatrix", camera->getViewMatrix());
        shader->setMatrix<decltype(camera->getProjectionMatrix())>("projectionMatrix", camera->getProjectionMatrix());

        dogTexture->bind();
        glBindVertexArray(geometry->getVao());

        /* 第一次绘制 */
        glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
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
        APP.setMouseButtonCallback(OnMouse);
        APP.setCursorPosCallback(OnCursorPos);
        APP.setScrollCallback(OnScroll);

        // opengl渲染的区域
        GL_CHECK_ERR(glViewport(0, 0, 800, 600));
        // 设置清屏颜色
        GL_CHECK_ERR(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

        prepareVao();
        prepareShader();
        prepareTexture();
        prepareCamera();
        prepareState();

        while (APP.update()) {
                cameraControl->update();
                render();
                // 绘制代码
        }
        APP.close();
        return 0;
}