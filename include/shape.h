/*
 * engine.h
 * Created on: Mar 27, 2024
 * Author: Italo Santana Seara
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <cmath>
#include "engine.h"

using namespace std;

/**
 * @class Shape
 * @brief The Shape class represents a shape that can be rendered on the screen.
 *
 * The Shape class is an abstract class that provides an interface for creating and rendering shapes on the screen.
 */
class Shape
{
public:
  virtual void render() = 0;
};

/**
 * @class Triangle
 * @brief The Triangle class represents a shape that can be rendered on the screen.
 *
 * The Triangle class is responsible for creating and managing the vertex buffer object (VBO) and vertex array object (VAO)
 * for a shape that can be rendered on the screen.
 */
class Triangle : public Shape
{
private:
  Engine *engine;

  GLfloat *verticies;
  GLuint VAO, VBO;

public:
  /**
   * @brief Constructs a Triangle object.
   *
   * This constructor initializes a Triangle object with the given `engine` parameter.
   * It also allocates memory for the `verticies` array and calls the `createBuffers()` function.
   *
   * @param engine A pointer to the Engine object.
   */
  Triangle(Engine *engine) : engine(engine)
  {
    this->verticies = new GLfloat[9]{};

    createBuffers();
  }

  /**
   * @brief Destructor for the Triangle class.
   *
   * This destructor is responsible for deleting the vertex array object (VAO) and the vertex buffer object (VBO)
   * associated with the Triangle object.
   */
  ~Triangle()
  {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
  }

  /**
   * Sets the vertex at the specified index to the given values.
   *
   * @param index The index of the vertex to set. Must be between 0 and 2 (inclusive).
   * @param verticie An array of three GLfloat values representing the new vertex coordinates.
   */
  void setVerticie(int index, GLfloat *verticie)
  {
    if (index < 0 || index > 2)
    {
      cerr << "Invalid verticie index: " << index << endl;
      return;
    }

    for (int i = 0; i < 3; i++)
    {
      verticies[index * 3 + i] = verticie[i];
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), verticies, GL_STATIC_DRAW);
  }

  /**
   * Creates the vertex buffers and vertex array object for the shape.
   */
  void createBuffers()
  {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), verticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  /**
   * Renders the shape using OpenGL.
   */
  void render()
  {
    glUseProgram(engine->getShaderProgram());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

/**
 * @class Rectangle
 * @brief Represents a rectangle shape in a 2D space.
 *
 * The Rectangle class provides functionality to create and manipulate rectangle shapes.
 * It is designed to work with an Engine object to render the rectangle on the screen.
 */
/**
 * @brief The Rectangle class represents a rectangle shape in a graphics engine.
 */
class Rectangle : public Shape
{
private:
  Engine *engine;

  int x, y;
  int width, height;

  Triangle *triangle1, *triangle2;

  /**
   * @brief Sets the vertices of the triangles based on the current position and size of the rectangle.
   */
  void setVertices()
  {
    GLfloat x1 = (GLfloat)x / engine->getWidth() * 2 - 1;
    GLfloat y1 = 1 - (GLfloat)y / engine->getHeight() * 2;
    GLfloat x2 = (GLfloat)(x + width) / engine->getWidth() * 2 - 1;
    GLfloat y2 = 1 - (GLfloat)y / engine->getHeight() * 2;
    GLfloat x3 = (GLfloat)x / engine->getWidth() * 2 - 1;
    GLfloat y3 = 1 - (GLfloat)(y + height) / engine->getHeight() * 2;
    GLfloat x4 = (GLfloat)(x + width) / engine->getWidth() * 2 - 1;
    GLfloat y4 = 1 - (GLfloat)(y + height) / engine->getHeight() * 2;

    triangle1->setVerticie(0, new GLfloat[3]{x1, y1, 0.0f});
    triangle1->setVerticie(1, new GLfloat[3]{x2, y2, 0.0f});
    triangle1->setVerticie(2, new GLfloat[3]{x3, y3, 0.0f});

    triangle2->setVerticie(0, new GLfloat[3]{x2, y2, 0.0f});
    triangle2->setVerticie(1, new GLfloat[3]{x3, y3, 0.0f});
    triangle2->setVerticie(2, new GLfloat[3]{x4, y4, 0.0f});
  }

public:
  /**
   * @brief Constructs a Rectangle object with the specified position and size.
   * @param engine Pointer to the graphics engine.
   * @param x The x-coordinate of the top-left corner of the rectangle.
   * @param y The y-coordinate of the top-left corner of the rectangle.
   * @param width The width of the rectangle.
   * @param height The height of the rectangle.
   */
  Rectangle(Engine *engine, int x, int y, int width, int height) : engine(engine), x(x), y(y), width(width), height(height)
  {
    triangle1 = new Triangle(engine);
    triangle2 = new Triangle(engine);

    setVertices();
  }

  /**
   * @brief Destructor for the Rectangle object.
   */
  ~Rectangle()
  {
    delete triangle1;
    delete triangle2;
  }

  /**
   * @brief Renders the rectangle on the screen.
   */
  void render()
  {
    triangle1->render();
    triangle2->render();
  }

  /**
   * @brief Sets the x-coordinate of the top-left corner of the rectangle.
   * @param x The new x-coordinate.
   */
  void setX(int x)
  {
    this->x = x;
    setVertices();
  }

  /**
   * @brief Sets the y-coordinate of the top-left corner of the rectangle.
   * @param y The new y-coordinate.
   */
  void setY(int y)
  {
    this->y = y;
    setVertices();
  }

  /**
   * @brief Sets the width of the rectangle.
   * @param width The new width.
   */
  void setWidth(int width)
  {
    this->width = width;
    setVertices();
  }

  /**
   * @brief Sets the height of the rectangle.
   * @param height The new height.
   */
  void setHeight(int height)
  {
    this->height = height;
    setVertices();
  }

  /**
   * @brief Returns the x-coordinate of the top-left corner of the rectangle.
   * @return The x-coordinate.
   */
  int getX() { return x; }

  /**
   * @brief Returns the y-coordinate of the top-left corner of the rectangle.
   * @return The y-coordinate.
   */
  int getY() { return y; }

  /**
   * @brief Returns the width of the rectangle.
   * @return The width.
   */
  int getWidth() { return width; }

  /**
   * @brief Returns the height of the rectangle.
   * @return The height.
   */
  int getHeight() { return height; }
};

#endif // SHAPE_H