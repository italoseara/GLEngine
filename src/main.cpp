#include <iostream>
#include "GLEngine/Engine.hpp"

using namespace std;

int speed = 250;
float x, y;

Engine::Circle circle;
Engine::Text text;

void init()
{
  x = Engine::Width() / 2;
  y = Engine::Height() / 2;

  circle = Engine::Circle({x, y}, 50, true);
  text = Engine::Text({0, 0});
}

void update(double dt)
{
  if (Engine::isKeyPressed('w'))
    y -= speed * dt;
  if (Engine::isKeyPressed('s'))
    y += speed * dt;
  if (Engine::isKeyPressed('a'))
    x -= speed * dt;
  if (Engine::isKeyPressed('d'))
    x += speed * dt;

  circle.pos = {x, y};
  text.text = "X: " + to_string(x) + ", Y: " + to_string(y);
}

void render()
{
  glColor3ub(255, 255, 255);
  circle.draw();

  glColor3ub(0, 255, 0);
  text.draw();
}

int main(int argc, char **argv)
{
  Engine::Init("App", 800, 600);
  Engine::Callbacks(init, update, render);
  Engine::Run(&argc, argv);
  return 0;
}