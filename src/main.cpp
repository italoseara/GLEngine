#include <iostream>
#include "engine.hpp"

using namespace std;

int cx = 400, cy = 300;

void update(double dt)
{
  if (Engine::isKeyPressed('W'))
    cy--;
  if (Engine::isKeyPressed('S'))
    cy++;
  if (Engine::isKeyPressed('A'))
    cx--;
  if (Engine::isKeyPressed('D'))
    cx++;
}

void render()
{
  glColor3ub(255, 0, 0);
  Engine::drawCircle(cx, cy, 50, true);

  glColor3ub(0, 255, 0);
  Engine::drawText(0, 0, "FPS: " + to_string(Engine::getFPS()));
  Engine::drawText(0, 30, "Test");
}

void shutdown()
{
}

int main(int argc, char **argv)
{
  Engine::init(&argc, argv, "My Game", 800, 600);
  Engine::setFPS(100);
  Engine::onUpdate(update);
  Engine::onRender(render);
  Engine::onShutdown(shutdown);
  Engine::run();
  return 0;
}