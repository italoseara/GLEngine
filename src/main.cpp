#include <iostream>
#include "engine.hpp"

using namespace std;

void init()
{
}

void update(double dt)
{
  log("FPS: %d", Engine::getFPS());
  log("Time: %f", dt);
}

void render()
{
  Engine::drawCircle(400, 300, 50);
  Engine::drawText(0, 0, "FPS: " + to_string(Engine::getFPS()));
  Engine::drawText(0, 30, "Test");
}

void input(unsigned char key, int x, int y)
{
  log("Key: %d", key);
}

void shutdown()
{
}

int main(int argc, char **argv)
{
  Engine::init(&argc, argv, "My Game", 800, 600);
  Engine::setFPS(60);
  Engine::onInit(init);
  Engine::onUpdate(update);
  Engine::onRender(render);
  Engine::onInput(input);
  Engine::onShutdown(shutdown);
  Engine::run();
  return 0;
}