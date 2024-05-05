#include <iostream>

#include "Models/Models.hpp"
#include "GLEngine/Engine.hpp"

using namespace std;

Polygon poly;
vector<Circle> points;

bool markers = true;

void init()
{
  cout << "Press SPACE to toggle markers" << endl;
  cout << "Press BACKSPACE to remove last point" << endl;
  cout << "Press ENTER to print points" << endl;
  cout << "LMB to add point" << endl;
  cout << "RMB to clear points" << endl;
  cout << "MMB to mirror points" << endl;
}

void update(double)
{
  poly.fill = !markers;
}

void render()
{
  Engine::Draw(poly, {255, 255, 255});

  Line line({Engine::getWidth() / 2.f, 0}, {Engine::getWidth() / 2.f, (float)Engine::getHeight()}, 1);
  if (markers)
    Engine::Draw(line, {255, 255, 255});

  Circle circle({Engine::getWidth() / 2.f, Engine::getHeight() / 2.f - 25}, 250, false);
  if (markers)
    Engine::Draw(circle, {255, 255, 255});

  for (auto &point : points)
    Engine::Draw(point, {255, 0, 0});
}

void keyDown(int keyCode)
{
  if (keyCode == KEY_SPACE)
    markers = !markers;

  if (keyCode == KEY_BACKSPACE)
  {
    poly.points.pop_back();
    points.pop_back();
  }

  if (keyCode == KEY_ENTER)
  {
    // Get the lowest x and y values from all points
    float minX = poly.points[0].x;
    float minY = poly.points[0].y;
    for (auto &point : poly.points)
    {
      if (point.x < minX)
        minX = point.x;
      if (point.y < minY)
        minY = point.y;
    }

    cout << "Points: {";
    for (auto &point : poly.points)
      cout << "{" << point.x - minX << ", " << point.y - minY << "}, ";
    cout << "}" << endl;
  }
}

void mouseAction(int button, int action, int x, int y)
{
  if (x > Engine::getWidth() / 2.f)
    return;

  if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
  {
    poly.points.push_back({(float)x, (float)y});
    points.push_back(Circle({x, y}, 5, true));
  }
  else if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
  {
    poly = Polygon();
    points.clear();
  }
  else if (button == GLUT_MIDDLE_BUTTON && action == GLUT_DOWN)
  {
    for (int i = poly.points.size() - 1; i >= 0; i--)
    {
      auto point = poly.points[i];
      poly.points.push_back({Engine::getWidth() - point.x, point.y});
      points.push_back(Circle({Engine::getWidth() - point.x, point.y}, 5, true));
    }
  }
}

int main(int argc, char **argv)
{
  Engine::Init("App", 300, 350, 60);
  Engine::Callbacks(init, update, render);
  Engine::InputCallbacks(keyDown);
  Engine::MouseCallbacks(mouseAction);
  Engine::Debug(false);
  Engine::Run(&argc, argv);
  return 0;
}