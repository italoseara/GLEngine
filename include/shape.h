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
 * @class Triangle
 * @brief The Triangle class represents a shape that can be rendered on the screen.
 *
 * The Triangle class is responsible for creating and managing the vertex buffer object (VBO) and vertex array object (VAO)
 * for a shape that can be rendered on the screen.
 */
class Triangle
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

class Rectangle
{
private:
  Engine *engine;

  int x, y;
  int width, height;

  Triangle *triangle1, *triangle2;

public:
  Rectangle(Engine *engine, int x, int y, int width, int height) : engine(engine), x(x), y(y), width(width), height(height)
  {
    triangle1 = new Triangle(engine);
    triangle2 = new Triangle(engine);

    setVerticies();
  }

  ~Rectangle()
  {
    delete triangle1;
    delete triangle2;
  }

  void render()
  {
    triangle1->render();
    triangle2->render();
  }

  void setVerticies()
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

  void setX(int x)
  {
    this->x = x;
    setVerticies();
  }

  void setY(int y)
  {
    this->y = y;
    setVerticies();
  }

  void setWidth(int width)
  {
    this->width = width;
    setVerticies();
  }

  void setHeight(int height)
  {
    this->height = height;
    setVerticies();
  }

  int getX() { return x; }
  int getY() { return y; }
  int getWidth() { return width; }
  int getHeight() { return height; }
};

#endif // SHAPE_H