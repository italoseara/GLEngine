#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <cmath>
#include <vector>

#include "Engine.hpp"

class Drawable
{
public:
  virtual void draw() = 0;
};

class Text : public Drawable
{
public:
  void *font;
  Vector2 pos;
  std::string text;

  Text() : font(GLUT_BITMAP_HELVETICA_12), pos(Vector2()), text("") {}
  Text(Vector2 pos, std::string text = "", void *font = GLUT_BITMAP_HELVETICA_12) : font(font), pos(pos), text(text) {}

  void draw() override
  {
    glPushMatrix();
    Vector2 p = Engine::Util::toScreen(pos.x, pos.y + glutBitmapHeight(font));
    glRasterPos2f(p.x, p.y);
    for (char c : text)
      glutBitmapCharacter(font, c);
    glPopMatrix();
  }
};

class Point : public Drawable
{
public:
  Vector2 pos;

  Point() : pos(Vector2()) {}
  Point(Vector2 pos) : pos(pos) {}
  Point(int x, int y) : pos(Vector2(x, y)) {}

  void draw() override
  {
    Vector2 p = Engine::Util::toScreen(pos.x, pos.y);
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
  }
};

class Line : public Drawable
{
public:
  Vector2 start, end;

  Line() : start(Vector2()), end(Vector2()) {}
  Line(Vector2 start, Vector2 end) : start(start), end(end) {}

  void draw() override
  {
    Vector2 p1 = Engine::Util::toScreen(start.x, start.y);
    Vector2 p2 = Engine::Util::toScreen(end.x, end.y);
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
  }
};

class Circle : public Drawable
{
public:
  Vector2 pos;
  int radius;
  bool fill;

  Circle() : pos(Vector2()), radius(0), fill(false) {}
  Circle(Vector2 pos, int radius, bool fill = false) : pos(pos), radius(radius), fill(fill) {}

  void draw() override
  {
    Vector2 p = Engine::Util::toScreen(pos.x, pos.y);
    glBegin(fill ? GL_POLYGON : GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
      float angle = i * M_PI / 180.0f;
      glVertex2f(p.x + cos(angle) * radius / Engine::Internal::width,
                 p.y + sin(angle) * radius / Engine::Internal::height);
    }
    glEnd();
  }
};

class Triangle : public Drawable
{
public:
  Vector2 p1, p2, p3;
  bool fill;

  Triangle() : p1(Vector2()), p2(Vector2()), p3(Vector2()), fill(false) {}
  Triangle(Vector2 p1, Vector2 p2, Vector2 p3, bool fill = false) : p1(p1), p2(p2), p3(p3), fill(fill) {}

  void draw() override
  {
    Vector2 p1 = Engine::Util::toScreen(this->p1.x, this->p1.y);
    Vector2 p2 = Engine::Util::toScreen(this->p2.x, this->p2.y);
    Vector2 p3 = Engine::Util::toScreen(this->p3.x, this->p3.y);
    glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);
    glEnd();
  }
};

class Rectangle : public Drawable
{
public:
  Vector2 pos;
  int width, height;
  bool fill;

  Rectangle() : pos(Vector2()), width(0), height(0), fill(false) {}
  Rectangle(Vector2 pos, int width, int height, bool fill = false) : pos(pos), width(width), height(height), fill(fill) {}

  void draw() override
  {
    Vector2 p1 = Engine::Util::toScreen(pos.x, pos.y);
    Vector2 p2 = Engine::Util::toScreen(pos.x + width, pos.y);
    Vector2 p3 = Engine::Util::toScreen(pos.x + width, pos.y + height);
    Vector2 p4 = Engine::Util::toScreen(pos.x, pos.y + height);
    glBegin(fill ? GL_QUADS : GL_LINE_LOOP);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);
    glVertex2f(p4.x, p4.y);
    glEnd();
  }
};

class Polygon : public Drawable
{
public:
  std::vector<Vector2> points;
  bool fill;

  Polygon() : points(std::vector<Vector2>()), fill(false) {}
  Polygon(std::vector<Vector2> points, bool fill = false) : points(points), fill(fill) {}

  void draw() override
  {
    glBegin(fill ? GL_POLYGON : GL_LINE_LOOP);
    for (Vector2 p : points)
    {
      Vector2 p1 = Engine::Util::toScreen(p.x, p.y);
      glVertex2f(p1.x, p1.y);
    }
    glEnd();
  }
};

class Shape : public Drawable
{
public:
  std::vector<Vector2> points;
  int method;

  Shape() : points(std::vector<Vector2>()), method(GL_LINE_LOOP) {}
  Shape(std::vector<Vector2> points, int method = GL_LINE_LOOP) : points(points), method(method) {}

  void draw()
  {
    glBegin(method);
    for (Vector2 p : points)
    {
      Vector2 p1 = Engine::Util::toScreen(p.x, p.y);
      glVertex2f(p1.x, p1.y);
    }
    glEnd();
  }
};

#endif // SHAPE_HPP