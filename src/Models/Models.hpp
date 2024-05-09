/*
 * Main models file, includes all models
 */

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
      *drawable += offset;
      *drawable += {400, 350};
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

// Sorry, it needs to be here, otherwise it won't compile (BodyPart is not defined)
#include "Faces.hpp"
#include "Eyes.hpp"
#include "Hairs.hpp"
#include "Mouths.hpp"
#include "Eyebrows.hpp"
#include "Noses.hpp"

#endif // MODELS_HPP