#ifndef MOUTHS_HPP
#define MOUTHS_HPP

#include "Models.hpp"

int selectedMouth = 0;

vector<BodyPart> mouths = {
  BodyPart( // 0
    {
      {new Line({0, 0}, {40, 0}, 7), {0, 0, 0}},
    }, {10, 100}
  ),
  BodyPart( // 1
    {
      {new Line({0, 10}, {10, 0}, 7), {0, 0, 0}},
      {new Line({-10, 0}, {0, 10}, 7), {0, 0, 0}},
    }, {25, 95}
  ),
  BodyPart( // 2
    {
      {new Triangle({-5, 15}, {25, -10}, {20, 15}, true), {0, 0, 0}},
      {new Triangle({8, 15}, {22, 3}, {20, 15}, true), {200, 0, 0}},
    }, {20, 95}
  ),
  BodyPart( // 3
    {
      {new Circle({0, 0}, 12, true), {0, 0, 0}},
      {new Circle({5, 5}, 5, true), {200, 0, 0}},
    }, {25, 100}
  ),
  BodyPart( // 4
    {
      {new Polygon({{0, 17}, {4, 23}, {42, 7}, {40, 0}}, true), {0, 0, 0}},
    }, {10, 85}
  ),
  BodyPart( // 5
    {
      {new Line({0, 20}, {20, 0}, 7), {0, 0, 0}},
      {new Line({0, 0}, {20, 20}, 7), {0, 0, 0}},
    }, {17, 90}
  ),
};

void drawMouth()
{
  mouths[selectedMouth].draw();
}

#endif // MOUTHS_HPP