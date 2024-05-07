#include <iostream>

#include "Models/Models.hpp"
#include "GLEngine/Engine.hpp"

using namespace std;

void drawBackground();
void spawnBubbles(int count);
void drawBody();
void drawInstructions();
string toOrdinal(int);

void init();
void update(double);
void render();
void keyDown(int key);

vector<Vector2> bubblePositions;

int main(int argc, char **argv)
{
  Engine::Init("App", 800, 600, 60);
  Engine::Callbacks(init, update, render);
  Engine::InputCallbacks(keyDown);
  Engine::Debug(false);
  Engine::Run(&argc, argv);
  return 0;
}

void init()
{
  srand(time(NULL));
  spawnBubbles(20);
}

void update(double)
{
}

void render()
{
  drawBackground();
  drawBody();

  drawFace();
  drawEyes();
  drawHair();

  // Line line({Engine::getWidth() / 2.f, 0}, {Engine::getWidth() / 2.f, (float)Engine::getHeight()}, 1);
  // Engine::Draw(line, {255, 255, 255});

  drawInstructions();
}

void keyDown(int key)
{
  if (key >= KEY_F1 && key <= KEY_F6)
    selectedFace = key - KEY_F1;
  
  if (key >= KEY_F7 && key <= KEY_F12)
    selectedHair = key - KEY_F7;

  if (key >= '1' && key <= '6')
    selectedEyeColor = key - '1';

  if (key == KEY_INSERT)
    Engine::Debug(!Engine::Internal::debug);
}

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
  void *font = GLUT_BITMAP_HELVETICA_18;
  vector<Text> lines({
      Text({10, 20}, "[F1 - F6] Face Outline", font),
      Text({250, 20}, toOrdinal(selectedFace + 1) + " Selected", font),
      Text({10, 45}, "[F7 - F12] Hair", font),
      Text({250, 45}, toOrdinal(selectedHair + 1) + " Selected", font),
      Text({10, 70}, "[1 - 6] Eye Color", font),
      Text({250, 70}, toOrdinal(selectedEyeColor + 1) + " Selected", font),
      Text({10, 95}, "[q, w, e, r, t, y] Mouth", font),
      Text({250, 95}, "0th Selected", font),
      Text({10, 120}, "[a, s, d, f, g, h] Eyebrows", font),
      Text({250, 120}, "0th Selected", font),
      Text({10, 145}, "[z, x, c, v, b, n] Nose", font),
      Text({250, 145}, "0th Selected", font),
  });

  for (Text line : lines)
    Engine::Draw(line, {255, 255, 255});
}

string toOrdinal(int n)
{
  if (n == 1)
    return "1st";
  if (n == 2)
    return "2nd";
  if (n == 3)
    return "3rd";
  return to_string(n) + "th";
}