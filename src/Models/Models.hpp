#ifndef MODELS_HPP
#define MODELS_HPP

#include <vector>
#include <iostream>
#include "../GLEngine/Engine.hpp"

using namespace std;

class BodyPart
{
public:
  vector<pair<Drawable *, Color>> parts;
  Vector2 offset;

  BodyPart(vector<pair<Drawable *, Color>> parts, Vector2 offset)
      : parts(parts), offset(offset)
  {
    for (pair<Drawable *, Color> &part : this->parts)
    {
      Drawable *drawable = part.first;
      *drawable += {400, 350};
      *drawable += offset;
    }
  }

  void draw()
  {
    for (pair<Drawable *, Color> &part : parts)
    {
      Engine::Draw(*part.first, part.second);
    }
  }
};

#include "Faces.hpp"

#endif // MODELS_HPP