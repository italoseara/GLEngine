#include <iostream>
#include "GLEngine/Engine.hpp"

using namespace std;

Shape drawing({}, GL_TRIANGLE_STRIP);
uint64_t cooldown = 0;

void init()
{
}

void update(double)
{
}

void render()
{
  Engine::Draw(drawing, {255, 255, 0});
}

void mouseDown(int button, int state, int x, int y)
{
  uint64_t now = Engine::getCurrentTimeMillis();
  if (now - cooldown < 100)
    return;

  if (state == GLUT_UP)
    return;

  cooldown = now;
  if (button == 0)
  {
    drawing.points.push_back({(float)x, (float)y});
  }
  else if (button == 2 && drawing.points.size() > 0)
  {
    drawing.points.pop_back();
  }
  else if (button == 1)
  {
    printf("Points: {");
    for (auto p : drawing.points)
    {
      printf("{%.0f, %.0f}", p.x, p.y);
      auto last = drawing.points.back();
      if (p.x != last.x || p.y != last.y)
        printf(", ");
    }
    printf("}\n");
  }
}

int main(int argc, char **argv)
{
  Engine::Init("App", 250, 250, 120);
  Engine::Callbacks(init, update, render);
  Engine::MouseCallbacks(mouseDown, nullptr);
  Engine::Run(&argc, argv);
  return 0;
}