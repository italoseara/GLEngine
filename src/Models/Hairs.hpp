#ifndef HAIRS_HPP
#define HAIRS_HPP

#define BLACK {0, 0, 0}

#include "Models.hpp"

int selectedHair = 0;

vector<BodyPart> hairs = {
  BodyPart( // 0
    {
      {new Shape({
        {3, 169}, {35, 118}, {0, 107}, {16, 40}, 
        {32, 118}, {59, 71}, {17, 49}, {68, 8}, 
        {61, 70}, {105, 70}, {70, 19}, {138, 0}, 
        {210, 28}, {103, 68}, {231, 32}, {246, 116}, 
        {260, 99}, {255, 172}, {185, 92}
      }, GL_TRIANGLE_STRIP), BLACK},
    },
    {-128, -145}
  ),
  BodyPart({}, {0, 0}) // 5 (Bald)
};

void drawHair()
{
  hairs[selectedHair].draw();
}

#endif // HAIRS_HPP