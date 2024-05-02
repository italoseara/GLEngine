#include <iostream>
#include "GLEngine/Engine.hpp"

using namespace std;

int speed = 250;
float x, y;

Engine::Circle circle;
Engine::Line line;
Engine::Text fpsText;
Engine::Text mouseText;

void init()
{
  x = Engine::getWidth() / 2;
  y = Engine::getHeight() / 2;

  circle = Engine::Circle({x, y}, 50, true);
  line = Engine::Line({0, 0}, {0, 0});
  fpsText = Engine::Text({0, 0});
  mouseText = Engine::Text({0, 20});
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
  line.start = {x, y};
  line.end = Engine::getMousePos();

  fpsText.text = "FPS: " + to_string(Engine::getFPS());
  mouseText.text = "Mouse: " + to_string(Engine::getMouseX()) + ", " + to_string(Engine::getMouseY()) + " " + (Engine::isMousePressed(0) ? "LMB " : "") + (Engine::isMousePressed(1) ? "RMB " : "") + (Engine::isMousePressed(2) ? "MMB " : "");
}

void render()
{
  glColor3ub(255, 255, 255);
  circle.draw();
  line.draw();

  glColor3ub(0, 255, 0);
  fpsText.draw();
  mouseText.draw();
}

int main(int argc, char **argv)
{
  Engine::Init("App", 800, 600, 120);
  Engine::Callbacks(init, update, render);
  Engine::Run(&argc, argv);
  return 0;
}