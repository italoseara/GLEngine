#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

/**
 * @class EBO
 * @brief Represents an OpenGL Element Buffer Object.
 *
 * The EBO class encapsulates an OpenGL Element Buffer Object, providing methods to create, bind, unbind, and remove the EBO.
 */
class EBO
{
private:
  GLuint id;

public:
  /**
   * @brief Constructs an empty EBO object.
   */
  EBO() {}

  /**
   * @brief Constructs an EBO object and initializes it with the specified vertex indices.
   *
   * @param indices The vertex indices to be stored in the EBO.
   * @param size The size of the vertex indices in bytes.
   */
  EBO(GLuint *indices, GLsizeiptr size);

  /**
   * @brief Binds the EBO to the current OpenGL context.
   */
  void bind();

  /**
   * @brief Unbinds the EBO from the current OpenGL context.
   */
  void unbind();

  /**
   * @brief Removes the EBO from the current OpenGL context.
   */
  void remove();
};

#endif // VBO_H