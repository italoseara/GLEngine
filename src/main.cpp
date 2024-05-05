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
  float halfWidth = Engine::getWidth() / 2.f;
  float halfHeight = Engine::getHeight() / 2.f;

  vector<Vector2> body({
      {halfWidth - 75, halfHeight + 300},
      {halfWidth + 75, halfHeight + 300},
      {halfWidth + 60, halfHeight + 110},
      {halfWidth - 60, halfHeight + 110},
  });

  Polygon shirt(body, true);
  Polygon shirtOutline(body, false);
  Engine::Draw(shirtOutline, {0, 0, 0});
  Engine::Draw(shirt, {228, 52, 39});
}

void drawInstructions()
{
  Text face({10, 40}, "[F1 - F6] Face Outline (" + to_string(selectedFace + 1) + " Selected)", GLUT_BITMAP_HELVETICA_18);
  Engine::Draw(face, {255, 255, 255});
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

  // Line line({Engine::getWidth() / 2.f, 0}, {Engine::getWidth() / 2.f, (float)Engine::getHeight()}, 1);
  // Engine::Draw(line, {255, 255, 255});

  drawInstructions();
}

void keyDown(int key)
{
  // Change selected face
  if (key >= KEY_F1 && key <= KEY_F6)
    selectedFace = key - KEY_F1;

  // Toggle debug mode
  if (key == KEY_ALT_L)
    Engine::Debug(!Engine::Internal::debug);
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