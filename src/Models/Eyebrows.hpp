#ifndef EYEBROWS_HPP
#define EYEBROWS_HPP

#include "Models.hpp"

int selectedEyebrow = 0;

vector<BodyPart> eyebrows = {
  BodyPart( // 0
    {
      {new Rectangle({0, 0}, 55, 10, true), {0, 0, 0}},
      {new Rectangle({115, 0}, 55, 10, true), {0, 0, 0}},
    }, {-85, -55}
  ),
  BodyPart( // 1
    {
      {new Rectangle({0, 0}, 55, 10, true), {0, 0, 0}},
      {new Rectangle({115, -10}, 55, 10, true), {0, 0, 0}},
    }, {-85, -55}
  ),
  BodyPart( // 2
    {
      {new Rectangle({0, 0}, 10, 10, true), {0, 0, 0}},
      {new Rectangle({15, 0}, 40, 10, true), {0, 0, 0}},
      {new Rectangle({115, 0}, 55, 10, true), {0, 0, 0}},
    }, {-85, -55}
  ),
  BodyPart( // 3
    {
      {new Rectangle({0, 0}, 10, 10, true), {0, 0, 0}},
      {new Rectangle({15, 0}, 40, 10, true), {0, 0, 0}},
      {new Rectangle({115, -10}, 55, 10, true), {0, 0, 0}},
    }, {-85, -55}
  ),
  BodyPart( // 4
    {
      {new Triangle({10, 0}, {0, 15}, {50, 30}, true), {0, 0, 0}},
      {new Triangle({90, 30}, {140, 15}, {130, 0}, true), {0, 0, 0}},
    }, {-70, -65}
  ),
  BodyPart( // 5
    {
      {new Rectangle({15, 0}, 35, 10, true), {0, 0, 0}},
      {new Rectangle({120, 0}, 35, 10, true), {0, 0, 0}},
    }, {-85, -55}
  ),
};

void drawEyebrow()
{
  eyebrows[selectedEyebrow].draw();

  // Set the color of the eyebrows to the hair color
  for (pair<Drawable *, Color> &part : eyebrows[selectedEyebrow].parts)
    part.second = hairs[selectedHair].parts[0].second;
}

#endif // EYEBROWS_HPP