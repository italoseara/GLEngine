#include <iostream>

#include "Models/Models.hpp"
#include "GLEngine/Engine.hpp"

using namespace std;

Shape poly({}, GL_TRIANGLE_STRIP);
vector<Circle> points;

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

}

void render()
{
  Engine::Draw(poly, {255, 255, 255});

  Circle circle({Engine::getWidth() / 2.f, Engine::getHeight() / 2.f - 25}, 250, false);
  Engine::Draw(circle, {255, 255, 255});

  for (auto &point : points)
    Engine::Draw(point, {255, 0, 0});
}

void keyDown(int keyCode)
{
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
  if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
  {
    poly.points.push_back({(float)x, (float)y});
    points.push_back(Circle({x, y}, 5, true));
  }
  else if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
  {
    poly = Shape({}, GL_TRIANGLE_STRIP);
    points.clear();
  }
}

int main(int argc, char **argv)
{
  Engine::Init("Draw hair", 300, 350, 60);
  Engine::Callbacks(init, update, render);
  Engine::InputCallbacks(keyDown);
  Engine::MouseCallbacks(mouseAction);
  Engine::Debug(false);
  Engine::Run(&argc, argv);
  return 0;
}