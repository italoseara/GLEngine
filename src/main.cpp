#include <iostream>
#include "engine.h"
#include "shape.h"

using namespace std;

class Game : public Engine
{
private:
  Triangle *triangle, *triangle2;
  Rectangle *rectangle;

public:
  Game(string title, int width, int height) : Engine(title, width, height) {}

  void init() override
  {
    triangle = new Triangle(this);
    triangle->setVerticie(0, new GLfloat[2]{-0.5f, -0.5f});
    triangle->setVerticie(1, new GLfloat[2]{0.5f, -0.5f});
    triangle->setVerticie(2, new GLfloat[2]{0.0f, 0.5f});

    triangle2 = new Triangle(this);
    triangle2->setVerticie(0, new GLfloat[2]{-0.5f, 0.5f});
    triangle2->setVerticie(1, new GLfloat[2]{0.5f, 0.5f});
    triangle2->setVerticie(2, new GLfloat[2]{0.0f, -0.5f});

    rectangle = new Rectangle(this, getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);
  }

  void update() override
  {
    rectangle->setX(rectangle->getX() + 1);
  }

  void render() override
  {
    clearColor(0.2f, 0.3f, 0.3f, 1.0f);

    setColor(255, 255, 255);
    rectangle->render();
  }

  void cleanup() override
  {
    delete triangle;
    delete triangle2;
    delete rectangle;
  }
};

int main()
{
  Game game("Teste", 800, 600);
  game.setDebug(true);
  game.run();

  return 0;
}
