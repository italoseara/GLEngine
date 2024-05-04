#include <iostream>

#include "Models/Models.hpp"
#include "GLEngine/Engine.hpp"

using namespace std;

vector<BodyPart> hairs;
vector<BodyPart> eyes;
vector<BodyPart> mouths;
vector<BodyPart> eyebrows;
vector<BodyPart> noses;

int selectedFace = 0;

vector<Vector2> bubblePositions;

void drawBackground()
{
  Engine::Clear({135, 196, 222});

  for (Vector2 pos : bubblePositions)
  {
    Circle c(pos, 100, true);
    Engine::Draw(c, {119, 188, 218});
  }
}

void spawnBubbles(int count)
{
  for (int i = 0; i < count; i++)
  {
    Vector2 bubblePos;
    bool overlap = false;
    do
    {
      bubblePos = {(float)(rand() % Engine::getWidth()), (float)(rand() % Engine::getHeight())};
      overlap = false;
      for (Vector2 pos : bubblePositions)
      {
        if (bubblePos.distance(pos) < 100)
        {
          overlap = true;
          break;
        }
      }
    } while (overlap);

    bubblePositions.push_back(bubblePos);
  }
}

void drawBody()
{
  // Rectangle rect({Engine::getWidth() / 2.f - 50, Engine::getHeight() / 2.f + 100}, 100, 200, true);
  Polygon shirt({
    {Engine::getWidth() / 2.f - 75, Engine::getHeight() / 2.f + 300},
    {Engine::getWidth() / 2.f + 75, Engine::getHeight() / 2.f + 300},
    {Engine::getWidth() / 2.f + 60, Engine::getHeight() / 2.f + 110},
    {Engine::getWidth() / 2.f - 60, Engine::getHeight() / 2.f + 110},
  }, true);
  Engine::Draw(shirt, {228, 52, 39});
  Polygon shirtOutline({
    {Engine::getWidth() / 2.f - 75, Engine::getHeight() / 2.f + 300},
    {Engine::getWidth() / 2.f + 75, Engine::getHeight() / 2.f + 300},
    {Engine::getWidth() / 2.f + 60, Engine::getHeight() / 2.f + 110},
    {Engine::getWidth() / 2.f - 60, Engine::getHeight() / 2.f + 110},
  }, false);
  Engine::Draw(shirtOutline, {0, 0, 0});
}

void init()
{
  // Change random seed
  srand(time(NULL));

  // Spawn random bubbles to fill the background
  spawnBubbles(20);
}

void update(double)
{
}

void render()
{
  drawBackground();
  drawBody();

  // Draw body parts
  faces[selectedFace].draw();
}

void keyDown(int key)
{
  if (key == 'h')
    Engine::Debug(!Engine::Internal::debug);
  if (key == '1')
    selectedFace = (selectedFace + 1) % faces.size();
}

int main(int argc, char **argv)
{
  Engine::Init("App", 800, 600, 60);
  Engine::Callbacks(init, update, render);
  Engine::InputCallbacks(keyDown);
  Engine::Debug(false);
  Engine::Run(&argc, argv);
  return 0;
}