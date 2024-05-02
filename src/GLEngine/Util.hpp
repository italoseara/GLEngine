#ifndef UTILS_HPP
#define UTILS_HPP

#include "Engine.hpp"

namespace Engine
{
  struct Vector2
  {
    float x, y;
    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2 &v) const { return Vector2(x + v.x, y + v.y); };
    Vector2 operator-(const Vector2 &v) const { return Vector2(x - v.x, y - v.y); };
    Vector2 operator*(float s) const { return Vector2(x * s, y * s); };
    Vector2 operator/(float s) const { return Vector2(x / s, y / s); };
  };

  struct Color
  {
    unsigned char r, g, b, a;
    Color() : r(0), g(0), b(0), a(255) {}
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) : r(r), g(g), b(b), a(a) {}
  };

  namespace Util
  {
    bool isOnScreen(int x, int y)
    {
      return x >= 0 && x <= Engine::Internal::width && y >= 0 && y <= Internal::height;
    }

    bool isKeyPressed(unsigned char key)
    {
      return Internal::keys[toupper(key)];
    }

    Vector2 toScreen(int x, int y)
    {
      return Vector2((float)x / (float)Internal::width - 1.0f, 1.0f - (float)y / (float)Internal::height);
    }
  }
}

#endif // UTILS_HPP