#ifndef NOSES_HPP
#define NOSES_HPP

#include "Models.hpp"

int selectedNose = 0;

vector<BodyPart> noses = {
  BodyPart({{new Line({{13, 0}, {0, 14}, {15, 21}}, 1), {0, 0, 0}}}, {-10, 35}), // 0
  BodyPart({{new Line({{14, 0}, {12, 15}, {0, 26}}, 1), {0, 0, 0}}}, {-13, 25}), // 1
  BodyPart({{new Line({{0, 8}, {7, 0}, {13, 9}}, 1), {0, 0, 0}},}, {-8, 40}), // 2
  BodyPart({{new Line({{8, 0}, {7, 11}, {0, 17}, {0, 26}, {6, 33}}, 1), {0, 0, 0}}}, {-8, 25}), // 3
  BodyPart({{new Line({{0, 0}, {14, 4}}, 1), {0, 0, 0}}}, {-10, 45}), // 4
  BodyPart({ // 5
      {new Circle({0, 0}, 15, true), {255, 0, 0}},
      {new Circle({0, 0}, 15, false), {0, 0, 0}}
    }, {-5, 45}
  ),
};

void drawNose()
{
  noses[selectedNose].draw();
}

#endif // NOSES_HPP