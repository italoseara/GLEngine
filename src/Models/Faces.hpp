#ifndef FACES_HPP
#define FACES_HPP

#include "Models.hpp"

#define BLACK {0, 0, 0}
#define LIGHT_SKIN {255, 219, 172}
#define BROWN_SKIN {135, 103, 90}

vector<BodyPart> faces = {
  BodyPart(
    { // Shouldn't have done this way because it is impossible to understand what each part is
      {new Polygon({
        {0, 0}, {2, 140}, {10, 220}, {50, 270}, 
        {200, 270}, {240, 220}, {248, 140}, {250, 0}, 
        {242, -12}, {230, -20}, {20, -20}, {8, -12}},
      true), LIGHT_SKIN},
      {new Polygon({
        {0, 0}, {2, 140}, {10, 220}, {50, 270}, 
        {200, 270}, {240, 220}, {248, 140}, {250, 0}, 
        {242, -12}, {230, -20}, {20, -20}, {8, -12}},
      false), BLACK},
    },
    {-125, -125}
  ),
  BodyPart(
    { // Shouldn't have done this way because it is impossible to understand what each part is
      {new Polygon({
        {0, 0}, {2, 140}, {10, 220}, {50, 270}, 
        {200, 270}, {240, 220}, {248, 140}, {250, 0}, 
        {242, -12}, {230, -20}, {20, -20}, {8, -12}},
      true), BROWN_SKIN},
      {new Polygon({
        {0, 0}, {2, 140}, {10, 220}, {50, 270}, 
        {200, 270}, {240, 220}, {248, 140}, {250, 0}, 
        {242, -12}, {230, -20}, {20, -20}, {8, -12}},
      false), BLACK},
    },
    {-125, -125}
  ),
  BodyPart(
    {
      {new Circle({25, 0}, 50, true), LIGHT_SKIN}, // Forehead left
      {new Circle({25, 0}, 50, false), BLACK}, // Forehead left (outline)
      {new Circle({225, 0}, 50, true), LIGHT_SKIN}, // Forehead right
      {new Circle({225, 0}, 50, false), BLACK}, // Forehead right (outline)
      {new Rectangle({25, -25}, 200, 25, true), LIGHT_SKIN}, // Forehead middle
      {new Line({25, -25}, {225, -25}, 1), BLACK}, // Forehead middle (outline)

      {new Circle({125, 140}, 250, true), LIGHT_SKIN}, // Chin
      {new Circle({125, 140}, 250, false), BLACK}, // Chin (outline)

      {new Rectangle({0, 0}, 250, 150, true), LIGHT_SKIN}, // Face
      {new Rectangle({0, 0}, 250, 150, false), BLACK}, // Face (outline)
      {new Line({1, 150}, {249, 150}, 5), LIGHT_SKIN}, // Erease bottom face line
      {new Line({1, 0}, {249, 0}, 5), LIGHT_SKIN}, // Erease top face line
    },
    {-125, -125}
  ),
  BodyPart(
    {
      {new Circle({25, 0}, 50, true), BROWN_SKIN}, // Forehead left
      {new Circle({25, 0}, 50, false), BLACK}, // Forehead left (outline)
      {new Circle({225, 0}, 50, true), BROWN_SKIN}, // Forehead right
      {new Circle({225, 0}, 50, false), BLACK}, // Forehead right (outline)
      {new Rectangle({25, -25}, 200, 25, true), BROWN_SKIN}, // Forehead middle
      {new Line({25, -25}, {225, -25}, 1), BLACK}, // Forehead middle (outline)

      {new Circle({125, 140}, 250, true), BROWN_SKIN}, // Chin
      {new Circle({125, 140}, 250, false), BLACK}, // Chin (outline)

      {new Rectangle({0, 0}, 250, 150, true), BROWN_SKIN}, // Face
      {new Rectangle({0, 0}, 250, 150, false), BLACK}, // Face (outline)
      {new Line({1, 150}, {249, 150}, 5), BROWN_SKIN}, // Erease bottom face line
      {new Line({1, 0}, {249, 0}, 5), BROWN_SKIN}, // Erease top face line
    },
    {-125, -125}
  ),
  BodyPart(
    {
      {new Triangle({0, 0}, {25, 0}, {25, -25}, true), LIGHT_SKIN}, // Forehead left
      {new Triangle({0, 0}, {25, 0}, {25, -25}, false), BLACK}, // Forehead left (outline)
      {new Triangle({225, 0}, {250, 0}, {225, -25}, true), LIGHT_SKIN}, // Forehead right
      {new Triangle({225, 0}, {250, 0}, {225, -25}, false), BLACK}, // Forehead right (outline)
      {new Line({25, -24}, {25, 0}, 1), LIGHT_SKIN}, // Erease forehead left line
      {new Rectangle({25, -25}, 200, 25, true), LIGHT_SKIN}, // Forehead middle
      {new Line({25, -25}, {225, -25}, 1), BLACK}, // Forehead middle (outline)

      {new Triangle({0, 215}, {250, 215}, {125, 275}, true), LIGHT_SKIN}, // Chin
      {new Triangle({0, 215}, {250, 215}, {125, 275}, false), BLACK}, // Chin (outline)

      {new Rectangle({0, 0}, 250, 215, true), LIGHT_SKIN}, // Face
      {new Rectangle({0, 0}, 250, 215, false), BLACK}, // Face (outline)
      {new Line({1, 215}, {249, 215}, 2), LIGHT_SKIN}, // Erease bottom face line
      {new Line({1, 0}, {249, 0}, 2), LIGHT_SKIN}, // Erease top face line
    },
    {-125, -125}
  ),
  BodyPart(
    {
      {new Triangle({0, 0}, {25, 0}, {25, -25}, true), BROWN_SKIN}, // Forehead left
      {new Triangle({0, 0}, {25, 0}, {25, -25}, false), BLACK}, // Forehead left (outline)
      {new Triangle({225, 0}, {250, 0}, {225, -25}, true), BROWN_SKIN}, // Forehead right
      {new Triangle({225, 0}, {250, 0}, {225, -25}, false), BLACK}, // Forehead right (outline)
      {new Line({25, -24}, {25, 0}, 1), BROWN_SKIN}, // Erease forehead left line
      {new Rectangle({25, -25}, 200, 25, true), BROWN_SKIN}, // Forehead middle
      {new Line({25, -25}, {225, -25}, 1), BLACK}, // Forehead middle (outline)

      {new Triangle({0, 215}, {250, 215}, {125, 275}, true), BROWN_SKIN}, // Chin
      {new Triangle({0, 215}, {250, 215}, {125, 275}, false), BLACK}, // Chin (outline)

      {new Rectangle({0, 0}, 250, 215, true), BROWN_SKIN}, // Face
      {new Rectangle({0, 0}, 250, 215, false), BLACK}, // Face (outline)
      {new Line({1, 215}, {249, 215}, 2), BROWN_SKIN}, // Erease bottom face line
      {new Line({1, 0}, {249, 0}, 2), BROWN_SKIN}, // Erease top face line
    },
    {-125, -125}
  ),
};

#endif // FACES_HPP
