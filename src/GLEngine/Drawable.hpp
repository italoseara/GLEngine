#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <cmath>
#include <vector>

#include "Engine.hpp"

class Drawable
{
public:
  virtual void draw(bool debug = false) = 0;
  virtual void operator+=(Vector2) {}
};

class Text : public Drawable
{
public:
  void *font;
  Vector2 pos;
  std::string text;

  Text() : font(GLUT_BITMAP_HELVETICA_12), pos(Vector2()), text("") {}
  Text(Vector2 pos, std::string text = "", void *font = GLUT_BITMAP_HELVETICA_12) : font(font), pos(pos), text(text) {}

  void draw(bool = false) override
  {
    glPushMatrix();
    glRasterPos2f(pos.x, pos.y + glutBitmapHeight(font));
    for (char c : text)
      glutBitmapCharacter(font, c);
    glPopMatrix();
  }

  void operator+=(Vector2 pos) override
  {
    this->pos += pos;
  }
};

class Point : public Drawable
{
public:
  Vector2 pos;

  Point() : pos(Vector2()) {}
  Point(Vector2 pos) : pos(pos) {}
  Point(int x, int y) : pos(Vector2(x, y)) {}

  void draw(bool debug = false) override
  {
    glBegin(GL_POINTS);
    glVertex2f(pos.x, pos.y);
    glEnd();

    if (debug)
    {
      glColor3ub(0, 255, 0);
      Text(pos, pos.toString()).draw();
      glColor3ub(255, 255, 255);
    }
  }

  void operator+=(Vector2 pos) override
  {
    this->pos += pos;
  }
};

class Line : public Drawable
{
public:
  Vector2 start, end;
  int width;

  Line() : start(Vector2()), end(Vector2()), width(1) {}
  Line(Vector2 start, Vector2 end, int width) : start(start), end(end), width(width) {}

  void draw(bool debug = false) override
  {
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(start.x, start.y);
    glVertex2f(end.x, end.y);
    glEnd();
    glLineWidth(1);

    if (debug)
    {
      glColor3ub(0, 255, 0);
      Text(start, start.toString()).draw();
      Text(end, end.toString()).draw();
      glColor3ub(255, 255, 255);
    }
  }

  void operator+=(Vector2 pos) override
  {
    start += pos;
    end += pos;
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

  void draw(bool debug = false) override
  {
    glBegin(fill ? GL_POLYGON : GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
      float angle = i * M_PI / 180.0f;
      float x = pos.x + radius * cos(angle);
      float y = pos.y + radius * sin(angle);
      glVertex2f(x, y);
    }
    glEnd();

    if (debug)
    {
      glColor3ub(0, 255, 0);
      Text(pos, pos.toString()).draw();
      Circle(pos, radius, false).draw();
      glColor3ub(255, 255, 255);
    }
  }

  void operator+=(Vector2 pos) override
  {
    this->pos += pos;
  }
};

class Triangle : public Drawable
{
public:
  Vector2 p1, p2, p3;
  bool fill;

  Triangle() : p1(Vector2()), p2(Vector2()), p3(Vector2()), fill(false) {}
  Triangle(Vector2 p1, Vector2 p2, Vector2 p3, bool fill = false) : p1(p1), p2(p2), p3(p3), fill(fill) {}

  void draw(bool debug = false) override
  {
    glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
    glVertex2f(this->p1.x, this->p1.y);
    glVertex2f(this->p2.x, this->p2.y);
    glVertex2f(this->p3.x, this->p3.y);
    glEnd();

    if (debug)
    {
      glColor3ub(0, 255, 0);
      Text(this->p1, this->p1.toString()).draw();
      Text(this->p2, this->p2.toString()).draw();
      Text(this->p3, this->p3.toString()).draw();
      Triangle(this->p1, this->p2, this->p3, false).draw();
      glColor3ub(255, 255, 255);
    }
  }

  void operator+=(Vector2 pos) override
  {
    p1 += pos;
    p2 += pos;
    p3 += pos;
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

  void draw(bool debug = false) override
  {
    Vector2 p1 = {pos.x, pos.y};
    Vector2 p2 = {pos.x + width, pos.y};
    Vector2 p3 = {pos.x + width, pos.y + height};
    Vector2 p4 = {pos.x, pos.y + height};
    glBegin(fill ? GL_QUADS : GL_LINE_LOOP);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p3.x, p3.y);
    glVertex2f(p4.x, p4.y);
    glEnd();

    if (debug)
    {
      glColor3ub(0, 255, 0);
      Text(pos, pos.toString()).draw();
      Text(Vector2(pos.x + width, pos.y), Vector2(pos.x + width, pos.y).toString()).draw();
      Text(Vector2(pos.x + width, pos.y + height), Vector2(pos.x + width, pos.y + height).toString()).draw();
      Text(Vector2(pos.x, pos.y + height), Vector2(pos.x, pos.y + height).toString()).draw();
      Rectangle(pos, width, height, false).draw();
      glColor3ub(255, 255, 255);
    }
  }

  void operator+=(Vector2 pos) override
  {
    this->pos += pos;
  }
};

class Polygon : public Drawable
{
public:
  std::vector<Vector2> points;
  bool fill;

  Polygon() : points(std::vector<Vector2>()), fill(false) {}
  Polygon(std::vector<Vector2> points, bool fill = false) : points(points), fill(fill) {}

  void draw(bool debug = false) override
  {
    glBegin(fill ? GL_POLYGON : GL_LINE_LOOP);
    for (Vector2 p : points)
    {
      Vector2 p1 = Vector2(p.x, p.y);
      glVertex2f(p1.x, p1.y);
    }
    glEnd();

    if (debug)
    {
      glColor3ub(0, 255, 0);
      for (size_t i = 0; i < points.size(); i++)
      {
        Vector2 p = points[i];
        Text(p, std::to_string(i)).draw();
      }
      Polygon(points, false).draw();
      glColor3ub(255, 255, 255);
    }
  }

  void operator+=(Vector2 pos) override
  {
    for (Vector2 &p : points)
      p += pos;
  }
};

class Shape : public Drawable
{
public:
  std::vector<Vector2> points;
  int method;

  Shape() : points(std::vector<Vector2>()), method(GL_LINE_LOOP) {}
  Shape(std::vector<Vector2> points, int method = GL_LINE_LOOP) : points(points), method(method) {}

  void draw(bool debug = false)
  {
    glBegin(method);
    for (Vector2 p : points)
    {
      Vector2 p1 = {p.x, p.y};
      glVertex2f(p1.x, p1.y);
    }
    glEnd();

    if (debug)
    {
      glColor3ub(0, 255, 0);
      for (size_t i = 0; i < points.size(); i++)
      {
        Vector2 p = points[i];
        Text(p, std::to_string(i)).draw();
      }
      Shape(points, GL_LINE_LOOP).draw();
      glColor3ub(255, 255, 255);
    }
  }

  void operator+=(Vector2 pos) override
  {
    for (Vector2 &p : points)
      p += pos;
  }
};

#endif // DRAWABLE_HPP