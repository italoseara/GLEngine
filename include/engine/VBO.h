#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

/**
 * @class VBO
 * @brief Represents an OpenGL Vertex Buffer Object.
 *
 * The VBO class encapsulates an OpenGL Vertex Buffer Object, providing methods to create, bind, unbind, and remove the VBO.
 */
class VBO
{
private:
  GLuint id;

public:
  /**
   * @brief Constructs an empty VBO object.
   */
  VBO() {}

  /**
   * @brief Constructs a VBO object and initializes it with the specified vertex data.
   *
   * @param vertices The vertex data to be stored in the VBO.
   * @param size The size of the vertex data in bytes.
   */
  VBO(GLfloat *vertices, GLsizeiptr size);

  /**
   * @brief Binds the VBO to the current OpenGL context.
   */
  void bind();

  /**
   * @brief Unbinds the VBO from the current OpenGL context.
   */
  void unbind();

  /**
   * @brief Removes the VBO from the current OpenGL context.
   */
  void remove();
};

#endif // VBO_H