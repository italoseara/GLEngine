#include <iostream>
#include "GLEngine/Engine.hpp"

using namespace std;

Engine::Circle circle;

void init()
{
  circle = Engine::Circle({100, 100}, 50, true);
}

void update(double)
{
}

void render()
{
  glColor3ub(255, 255, 255);
  circle.draw();
}

int main(int argc, char **argv)
{
  Engine::Init("Engine", 800, 600);
  Engine::Callbacks(init, update, render);
  Engine::Run(&argc, argv);
  return 0;
}