//
//  Window.cpp
//  Graphics
//
//  Created by Edwin Solis on 10/5/20.
//

#include <Window.h>
#include <Shader.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexBufferLayout.h>
#include <Texture.h>
#include <Renderer.h>
#include "math.h"
#include "matrix_transform.h"
#include <Camera.h>
#include <Cube.h>
#include "stb_image.h"
#include <Model.h>
#include <iostream>

static Renderer* renderer = new Renderer();
static Shader* shader;
static Shader* lightShader;
static float timef = 0.0f;
static Camera camera;
static float step = 0.03f;
static bool keys[1024];
static bool firstMouse = true;
static double lastX, lastY;
static float sensitivity = 0.005f;
static double lastTime, currentTime, deltaTime;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;
    
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = lastX - xpos, yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    camera.RotatePitch(yoffset * sensitivity);
    camera.RotateYaw(xoffset * sensitivity);
}

void movement(GLFWwindow* window)
{
        if(keys[GLFW_KEY_ESCAPE])
            glfwSetWindowShouldClose(window, GL_TRUE);
        if (keys[GLFW_KEY_W])
            camera.MoveForward(step);
        if (keys[GLFW_KEY_S])
            camera.MoveForward(-step);
        if (keys[GLFW_KEY_A])
            camera.MoveRight(-step);
        if (keys[GLFW_KEY_D])
            camera.MoveRight(step);
        if(keys[GLFW_KEY_SPACE])
            camera.MoveUp(step);
        if(keys[GLFW_KEY_LEFT_SHIFT])
            camera.MoveUp(-step);
        if(keys[GLFW_KEY_UP])
            camera.RotatePitch(step);
        if(keys[GLFW_KEY_DOWN])
            camera.RotatePitch(-step);
        if(keys[GLFW_KEY_LEFT])
            camera.RotateYaw(step);
        if(keys[GLFW_KEY_RIGHT])
            camera.RotateYaw(-step);
        if(keys[GLFW_KEY_Q])
            camera.RotateRoll(-step);
        if(keys[GLFW_KEY_E])
            camera.RotateRoll(step);
}

Window::Window(unsigned int width, unsigned int height, const char* title)
:_width(width), _height(height), _title(title)
{
    if(!glfwInit())
        Close();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    _glfwWindow = glfwCreateWindow(_width, _height, _title, NULL, NULL);
    /*
    int imageHeight, imageWidth;
    unsigned char* buffer = stbi_load("assets/images/icon.png", &imageWidth, &imageHeight, nullptr, 4);
    GLFWimage image;
    image.width = imageWidth; image.height = imageHeight; image.pixels = buffer;
    glfwSetWindowIcon(_glfwWindow, 1, &image);
    stbi_image_free(buffer);
    */
    if(_glfwWindow == nullptr)
    {
        std::cout << "Error creating window context" << std::endl;
        Close();
    }
    
    std::cout << glfwGetVersionString() << std::endl;
    
    glfwMakeContextCurrent(_glfwWindow);
    //glViewport(0, 0, _width, _height);
    
    glfwSetKeyCallback(_glfwWindow, key_callback);
    glfwSetInputMode(_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(_glfwWindow, mouse_callback);
    _new = true;
}

void Window::Render()
{
    BackgroundColor(stml::vec4f(0.05f, 0.01f, 0.01f, 1.0f));
    Run();
    glfwSwapBuffers(_glfwWindow);
    glfwPollEvents();
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    
    //std::cout << deltaTime << " ms\n";
}

void Window::Run()
{
    if(NewFrame())
        Frame();
    //stml::mat4f model = stml::multiply(stml::scale(2.0f, 2.0f, 1.0f), stml::translate(0.0f, 2.0f*sinf(timef), 2.0f)); //Translate then scale
    //stml::mat4f model = stml::multiply(stml::translate(0.0f, 2.0f*sinf(timef), 2.0f), stml::scale(2.0f, 2.0f, 1.0f)); //Scale then translate
    
    
    stml::vec3f cubePositions[] = {
        stml::vec3f(3.1f, -2.7f, 4.0f),
        stml::vec3f(2.0f, 5.0f, -15.0f),
        stml::vec3f(-1.5f, -2.2f, -2.5f),
        stml::vec3f(-3.8f, -2.0f, -12.3f),
        stml::vec3f(2.4f, -0.4f, 3.5f),
        stml::vec3f(-1.7f, 3.0f, -7.5f),
        stml::vec3f(1.3f, -2.0f, 2.5f),
        stml::vec3f(1.5f, 2.0f, -2.5f),
        stml::vec3f(1.5f, 0.2f, 1.5f),
        stml::vec3f(-1.3f, 1.0f, -1.5f),
        stml::vec3f(0.0f,0.0f,0.0f)
    };
    
    //stml::vec3f lightPos(0.0f , 4.0f * sinf(timef), 4.0f*cosf(timef));
    //PointLight light(lightPos, stml::vec3f(0.0f), stml::vec3f(0.0f), stml::vec3f(0.0f), stml::vec3f(1.0f, 0.009f, 0.0032f));
    float color = 0.6f;
    DirectionalLight dirLight(stml::vec3f(0.0f, sinf(timef), cosf(timef)), stml::vec3f(0.3f), stml::vec3f(0.01f), stml::vec3f(0.01f));
    SpotLight spotlight(camera.GetCameraPosition(), camera.GetCameraDirection(), cosf(stml::radians(10.0f)), cosf(stml::radians(20.0f)), stml::vec3f(0.0f), stml::vec3f(color), stml::vec3f(color), stml::vec3f(1.0f, 0.009f, 0.0032f));
    PointLight plight1(stml::vec3f(1.0f, 2.0f, 3.0f), stml::vec3f(0.01f, 0.005f, 0.005f), stml::vec3f(0.1f, 0.0f, 0.0f), stml::vec3f(0.1f), stml::vec3f(1.0f, 0.009f, 0.0032f));
    PointLight plight2(stml::vec3f(-2.0f, 4.0f, -2.5f), stml::vec3f(0.01f, 0.005f, 0.005f), stml::vec3f(0.1f, 0.0f, 0.0f), stml::vec3f(0.1f), stml::vec3f(1.0f, 0.009f, 0.0032f));
    PointLight plight3(stml::vec3f(5.0f, 0.0f, -1.0f), stml::vec3f(0.01f, 0.005f, 0.005f), stml::vec3f(0.1f, 0.0f, 0.0f), stml::vec3f(0.1f), stml::vec3f(1.0f, 0.009f, 0.0032f));
    PointLight plight4(stml::vec3f(0.0f), stml::vec3f(0.01f, 0.005f, 0.005f), stml::vec3f(0.1f, 0.0f, 0.0f), stml::vec3f(0.1f), stml::vec3f(1.0f, 0.009f, 0.0032f));
    
    PointLight lights[4] = {plight1, plight2, plight3, plight4};
    stml::mat4f view = camera.GetCameraView();
    stml::mat4f proj = stml::perspective(stml::radians(45.0f), 800.0f/600.0f, 0.01f, 30.0f);
    stml::vec3f lightColor(0.2f, 0.0f, 0.0f);
    
    //lightShader->Unbind();
    shader->Bind();
    shader->SetUniformMat4f("u_view", view);
    shader->SetUniformMat4f("u_projection", proj);
    shader->SetUniform3f("u_ViewPos", camera.GetCameraPosition());
    shader->SetUniformMaterialMap("u_Material", material_wood);
    //shader->SetUniformPointLight("u_PointLight", light);
    shader->SetUniformPointLight("u_PointLight[0]", lights[0]);
    shader->SetUniformPointLight("u_PointLight[1]", lights[1]);
    shader->SetUniformPointLight("u_PointLight[2]", lights[2]);
    shader->SetUniformPointLight("u_PointLight[3]", lights[3]);
    
    shader->SetUniformDirectionalLight("u_DirLight", dirLight);
    shader->SetUniformSpotLight("u_SpotLight", spotlight);
    
    /*
    lightShader->Bind();
    lightShader->SetUniformMat4f("u_view", view);
    lightShader->SetUniformMat4f("u_projection", proj);
    lightShader->SetUniform3f("u_color", lightColor);
     */
    //lightShader->SetUniformMat4f("u_model", stml::translate(lightPos));
    
    //shader->SetUniformMat4f("u_projection", stml::ortho(-8.0f, 8.0f, -6.0f, 6.0f, -5.0f, 5.0f));
    
    GLCALL(glStencilFunc(GL_ALWAYS, 1, 0xFF));
    GLCALL(glStencilMask(0xFF));
    shader->SetUniform1b("u_Draw", true);
    for(int i = 0; i < 10; ++i)
    {
        shader->Bind();
        stml::mat4f model = stml::translate(cubePositions[i]);//stml::multiply(stml::translate(cubePositions[i]), stml::rotateY(timef));
        shader->SetUniformMat4f("u_model", model);
        renderer->Draw();
    }
    
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    //glDisable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);
    
    shader->SetUniform1b("u_Draw", false);
    for(int i = 0; i < 10; ++i)
    {
        shader->Bind();
        stml::mat4f model = /*stml::translate(cubePositions[i]);*/stml::multiply(stml::translate(cubePositions[i]), /*stml::multiply(stml::rotateY(timef), */stml::scale(1.01f));
        shader->SetUniformMat4f("u_model", model);
        renderer->Draw();
    }
    
    
    /*
    for(int i = 0; i<3; ++i)
    {
        lightShader->Bind();
        lightShader->SetUniformMat4f("u_model", stml::translate(lights[i].GetPosition()));
        renderer->Draw();
    }

    lightShader->SetUniformMat4f("u_model", stml::translate(stml::vec3f(0.0f, -10.0 * sinf(timef), -10.0f * cosf(timef))));
     */
    //renderer->Draw();
    timef += 0.01f;
    //camera.SetPosition(stml::vec3f(sinf(timef), 0.0f, 0.0f));
    movement(_glfwWindow);
}


//void Window::Frame()
//{
//    /*
//    GLuint index[] = {
//        0, 1, 2,
//        1, 2, 3
//    };
//
//    GLfloat vertices[] = {
//        -0.5f,  0.5f, 1.0f,
//         0.5f,  0.5f, 1.0f,
//        -0.5f, -0.5f, 1.0f,
//         0.5f, -0.5f, 1.0f
//    };
//
//    GLfloat positions[] = {
//        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
//         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
//         0.5f, -0.5f, 0.0f, 1.0f, 0.0f
//    };*/
//    VertexBufferLayout textLayout;
//    textLayout.Push<float>(3);
//    textLayout.Push<float>(2);
//    textLayout.Push<float>(3);
//
//    VertexArray* vaoText = new VertexArray(textLayout);
//    //VertexBuffer* vboText = new VertexBuffer(positions, sizeof(positions));
//    //IndexBuffer* ibo = new IndexBuffer(index, 6);
//    //vaoText->AddBuffer(*vboText, *ibo);
//
//
//
//    /*
//    VertexBufferLayout layout;
//    layout.Push<float>(3);
//
//    VertexBuffer* vbo = new VertexBuffer(vertices, sizeof(vertices));
//    VertexArray* vao = new VertexArray(layout);
//    vao->AddBuffer(*vbo, *ibo);
//    */
//    //shader = new Shader("assets/shaders/projection.shader");
//    shader = new Shader("assets/shaders/main.shader");
//    shader->Bind();
//    //shader->SetUniform3f("u_AmbientColor", stml::vec3f(0.1f, 0.1f, 0.1f));
//    shader->SetUniform3f("u_AmbientColor", stml::vec3f(0.0f));
//    shader->SetUniform3f("u_LightColor", stml::vec3f(1.0f, 1.0f, 1.0f));
//    shader->SetUniform1f("u_specularStrength", 1.0f);
//
//
//    shader->SetUniform1i("u_Texture", 0);
//    renderer->PushToQueue(*vaoText, *shader);
//
//    Texture* texture = new Texture("assets/textures/texture.jpg");
//    Texture* container = new Texture("assets/textures/container.png");
//    Texture* containerSpecular = new Texture("assets/textures/container2_specular.png");
//
//    texture->Bind();
//    container->Bind(1);
//    containerSpecular->Bind(2);
//
//    Cube cube(0.5f, stml::vec3f(0.0f, 0.0f, 0.0f), texture);
//    VertexBuffer* cubevb = new VertexBuffer(cube.GenVertexBuffer().GetData(), cube.GenVertexBuffer().GetSize() * sizeof(float));
//    IndexBuffer* cubeib = new IndexBuffer(cube.GenIndexBuffer().GetData(), cube.GenIndexBuffer().GetSize());
//    vaoText->AddBuffer(*cubevb, *cubeib);
//    shader->Unbind();
//
//
//    lightShader = new Shader("assets/shaders/light.shader");
//    lightShader->Bind();
//    VertexBufferLayout lightLayout;
//    lightLayout.Push<float>(3);
//    lightLayout.Push<float>(2);
//    lightLayout.Push<float>(3);
//
//    VertexArray* lightVAO = new VertexArray(lightLayout);
//    Cube lightcube(0.1f, stml::vec3f(0.0f, 0.0f, 0.0f), nullptr);
//    VertexBuffer* lightvbo = new VertexBuffer(lightcube.GenVertexBuffer().GetData(), lightcube.GenVertexBuffer().GetSize() * sizeof(float));
//    IndexBuffer* lightibo = new IndexBuffer(lightcube.GenIndexBuffer().GetData(), lightcube.GenIndexBuffer().GetSize());
//    lightVAO->AddBuffer(*lightvbo, *lightibo);
//    renderer->PushToQueue(*lightVAO, *lightShader);
//    lightShader->Unbind();
//    _new = false;
//}


void Window::BackgroundColor(const stml::vec4f& color) const
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    //GLCALL(glClearColor(0.2f, 0.3f, 0.6f, 1.0f));
    GLCALL(glClearColor(color.x, color.y, color.z, color.w));
    GLCALL(glEnable(GL_DEPTH_TEST));
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCALL(glEnable(GL_STENCIL_TEST));
    //GLCALL(glStencilFunc(GL_ALWAYS, 1, 0xFF));
    GLCALL(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
    GLCALL(glStencilFunc(GL_ALWAYS, 1, 0xFF));
    GLCALL(glStencilMask(0xFF));
}


void Window::Close() const
{
    glfwTerminate();
}

Window::~Window()
{
    delete renderer;
}

void Window::Frame()
{
    Texture container = Texture("assets/textures/container.png", "texture_diffuse");
    Texture containerSpecular = Texture("assets/textures/container2_specular.png", "texture_specular");
    std::vector<Texture> textures;
    textures.push_back(container);
    textures.push_back(containerSpecular);
    Model model("assets/models/nanosuit/nanosuit.obj");
    //Model model("assets/models/backpack.obj");
    Cube cube(0.5f, stml::vec3f(0.0f, 0.0f, 0.0f), textures);
    shader = new Shader("assets/shaders/main.shader");
    renderer->PushToQueue(cube.GenMesh(), *shader);
    
    for(const auto& mesh : model.GetMeshes())
        renderer->PushToQueue(mesh, *shader);
    
    _new = false;
}
