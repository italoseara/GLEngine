#include <iostream>
#include <string>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/engine.h"
#include "engine/shaders.h"
#include "engine/VAO.h"
#include "engine/VBO.h"
#include "engine/EBO.h"

using namespace std;

class Game : public Engine
{
private:
  Shader shader;
  VAO vao;
  VBO vbo;
  EBO ebo;
  GLuint uniId;

public:
  Game(string title, int width, int height, bool debug = false) : Engine(title, width, height, debug)
  {
  }

  void init() override
  {
    string shader_path = "/home/italo-seara/dev/OpenGL/src/shaders";
    shader = Shader(shader_path + "/default.vert", shader_path + "/default.frag");

    GLfloat vertices[] =
        {
            // Position                                    // Color
            -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f,   // Lower left corner
            0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f,    // Lower right corner
            0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f, 0.32f, // Upper corner
            -0.25f, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f,  // Inner left
            0.25f, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f,   // Inner right
            0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f     // Inner down
        };
    GLuint indices[] =
        {
            0, 3, 5, // Lower left triangle
            3, 2, 4, // Lower right triangle
            5, 4, 1  // Upper triangle
        };

    vao = VAO();
    vao.bind();

    vbo = VBO(vertices, sizeof(vertices));
    ebo = EBO(indices, sizeof(indices));

    vao.link(vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void *)0);                     // Link for vertex coordinates
    vao.link(vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat))); // Link for vertex colors
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    uniId = glGetUniformLocation(shader.get_id(), "scale");
  }

  void update() override
  {
  }

  void render() override
  {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.activate();
    glUniform1f(uniId, 0.5f);
    vao.bind();

    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
  }

  void shutdown() override
  {
    vao.remove();
    vbo.remove();
    ebo.remove();
    shader.remove();
  }
};

int main(int argc, char const *argv[])
{
  Game game("OpenGL Engine", 800, 800, true);
  game.run();
  return 0;
}
