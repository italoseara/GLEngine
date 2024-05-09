#ifndef EYES_HPP
#define EYES_HPP

#include "Models.hpp"

#define min(a, b) (a < b ? a : b)

BodyPart eyes({
  {new Circle({0, 0}, 45, true), {255, 255, 255}},
  {new Circle({115, 0}, 45, true), {255, 255, 255}},
  {new Circle({0, 0}, 45, false), {0, 0, 0}},
  {new Circle({115, 0}, 45, false), {0, 0, 0}},
}, {-58, 0});

BodyPart pupils({
  {new Circle({0, 0}, 15, true), {0, 0, 0}},
  {new Circle({115, 0}, 15, true), {0, 0, 0}},
}, {-58, 0});

vector<Color> eyeColors = {
  {0, 0, 0},     // Black
  {69, 24, 0},   // Brown
  {84, 42, 14},  // Dark Brown
  {46, 83, 111}, // Aqua
  {28, 120, 71}, // Green
  {200, 20, 20}, // Red
};

int selectedEyeColor = 0;

void drawEyes()
{
  eyes.draw();

  // Change the pupils' position based on the mouse position
  Vector2 mouse = Engine::getMousePos();

  Vector2 leftPos = Vector2(0, 0) + eyes.offset + Vector2(400, 350);
  Vector2 rightPos = Vector2(115, 0) + eyes.offset + Vector2(400, 350);
  Vector2 centerPos = Vector2(57, 0) + eyes.offset + Vector2(400, 350);
  float radius = 25;

  Vector2 leftDist = mouse - centerPos;
  Vector2 rightDist = mouse - centerPos;

  leftPos = (leftDist.normalize() * min(leftDist.magnitude(), radius)) + leftPos;
  rightPos = (rightDist.normalize() * min(rightDist.magnitude(), radius)) + rightPos;

  auto leftPair = &pupils.parts[0];
  auto rightPair = &pupils.parts[1];

  Circle *leftPupil = (Circle *)(leftPair->first);
  Circle *rightPupil = (Circle *)(rightPair->first);

  leftPupil->pos = leftPos;
  rightPupil->pos = rightPos;

  // Change the pupils' color
  leftPair->second = eyeColors[selectedEyeColor];
  rightPair->second = eyeColors[selectedEyeColor];

  pupils.draw();
}

#endif // EYES_HPP