#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Canis/Canis.hpp"
#include "Canis/Window.hpp"
#include "Canis/Shader.hpp"
#include "Canis/Debug.hpp"
#include "Canis/IOManager.hpp"
#include "Canis/InputManager.hpp"
#include "Canis/Camera.hpp"

// git restore .
// git fetch
// git pull

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float vertices[] = {
    // positions           // texture coords
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

// world space positions of our cubes
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)};

int main(int argc, char *argv[])
{
    Canis::Init();
    Canis::InputManager inputManager;

    using namespace glm;

    /// SETUP WINDOW
    Canis::Window window;


    unsigned int flags = 0;

    if (Canis::GetProjectConfig().fullscreen)
        flags |= Canis::WindowFlags::FULLSCREEN;

    window.Create("Hello Triangle",
                  Canis::GetProjectConfig().width,
                  Canis::GetProjectConfig().heigth,
                  flags);
    /// END OF WINDOW SETUP

    glEnable(GL_DEPTH_TEST);

    /// SETUP SHADER
    Canis::Shader shader;
    shader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    shader.AddAttribute("aPosition");
    shader.Link();
    /// END OF SHADER

    /// Load Image
    Canis::GLTexture texture = Canis::LoadImageGL("assets/textures/BlebhDzIcAALt8a.png");
    /// End of Image Loading

    /// SETUP MODEL
    /*float vertices[] = {
        // vertices in counter clockwise order
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // top right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // top right
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // top left
    };*/

    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /// END OF MODEL

    // wireframe
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    // fill
    // glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

    unsigned int lastTime = SDL_GetTicks();

    while (inputManager.Update(Canis::GetProjectConfig().width,
                               Canis::GetProjectConfig().heigth))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        shader.SetVec3("COLOR", 0.0f, 0.0f, 1.0f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        shader.SetInt("MEMETEXTURE", 0);

        using namespace glm;

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 project = glm::mat4(1.0f);
        view = translate(view, vec3(0.0f,0.0f, -3.0f));
        project = perspective(radians(45.0f),
            (float)window.GetScreenWidth() / (float)window.GetScreenHeight(),
            0.01f, 100.0f);

        shader.SetMat4("VIEW", view);
        shader.SetMat4("PROJECTION", project);

        for(int i = 0; i < sizeof(cubePositions)/sizeof(vec3); i++)
        {
            //cubePositions[i].y -= 0.001f;
            cubePositions[i].y -= 5.0f*((SDL_GetTicks() - lastTime)/1000.0f);
            //cubePositions[i].y -= gravity * Time.deltaTime;
        }

        // for(glm::vec3 pos : cubePositions)
        for(int i = 0; i < sizeof(cubePositions)/sizeof(vec3); i++)
        {
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, cubePositions[i]);
            //transform = glm::rotate(transform, (float)SDL_GetTicks() * 0.001f, glm::vec3(1.0f, 0.0f, 1.0f));
            transform = glm::scale(transform, glm::vec3(0.5f));

            shader.SetMat4("TRANSFORM", transform);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, (sizeof(vertices)/sizeof(float))/5);
            glBindVertexArray(0);
        }

        shader.UnUse();

        window.SwapBuffer();
        lastTime = SDL_GetTicks();
        SDL_Delay(5);
    }

    return 0;
}