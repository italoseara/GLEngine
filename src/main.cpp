#include <iostream>

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

public:
  Game(string title, int width, int height, bool debug = false) : Engine(title, width, height, debug)
  {
  }

  void init() override
  {
    string shader_path = "/home/italo-seara/dev/OpenGL/src/shaders";
    shader = Shader(shader_path, "vertex.glsl", "fragment.glsl");

    GLfloat vertices[] = {-0.5f, -0.5f, 0.0f,
                          0.5f, -0.5f, 0.0f,
                          0.0f, 0.5f, 0.0f};
    GLuint indices[] = {0, 1, 2};

    vao = VAO();
    vao.bind();

    vbo = VBO(vertices, sizeof(vertices));
    ebo = EBO(indices, sizeof(indices));

    vao.linkVBO(vbo, 0);
    vao.unbind();
    vbo.unbind();
    ebo.unbind();
  }

  void update() override
  {
  }

  void render() override
  {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    vao.bind();

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
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
  Game game("OpenGL Engine", 800, 600, true);
  game.run();
  return 0;
}
