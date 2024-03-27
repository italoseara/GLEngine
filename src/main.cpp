#include <iostream>
#include "engine.h"

using namespace std;

class Game : public Engine
{
public:
  Game(string title, int width, int height) : Engine(title, width, height) {}

  void init() override
  {
    cout << "[GAME] Hello, from Game!\n";
  }

  void update() override
  {
    cout << "[GAME] FPS: " << getFps() << "\n";
    cout << "[GAME] DeltaTime: " << getDeltaTime() << "s\n";
  }

  void render() override
  {
    cout << "[GAME] Rendering...\n";

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void cleanup() override
  {
    cout << "[GAME] Goodbye, from Game!\n";
  }
};

int main()
{
  Game game("Teste", 800, 600);
  game.setDebug(true);
  game.run();

  return 0;
}
