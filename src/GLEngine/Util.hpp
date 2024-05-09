#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include "Engine.hpp"

struct Vector2
{
  float x, y;
  Vector2() : x(0), y(0) {}
  Vector2(float x, float y) : x(x), y(y) {}

  Vector2 operator+(const Vector2 &v) const { return Vector2(x + v.x, y + v.y); };
  Vector2 operator-(const Vector2 &v) const { return Vector2(x - v.x, y - v.y); };
  Vector2 operator*(float s) const { return Vector2(x * s, y * s); };
  Vector2 operator/(float s) const { return Vector2(x / s, y / s); };
  Vector2 operator+=(const Vector2 &v) { return *this = *this + v; };
  Vector2 operator-=(const Vector2 &v) { return *this = *this - v; };

  float magnitude() const { return std::sqrt(x * x + y * y); }
  float distance(const Vector2 &v) const { return (*this - v).magnitude(); }
  Vector2 normalize() const { return *this / magnitude(); }

  std::string toString() const
  {
    char buff[100];
    snprintf(buff, sizeof(buff), "{%.1f, %.1f}", x, y);
    std::string buffAsStdStr = buff;
    return buffAsStdStr;
  }
};

struct Color
{
  unsigned char r, g, b, a;
  Color() : r(0), g(0), b(0), a(255) {}
  Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) : r(r), g(g), b(b), a(a) {}
};

#endif // UTILS_HPP