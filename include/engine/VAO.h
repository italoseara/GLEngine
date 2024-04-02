#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"

/**
 * @class VAO
 * @brief Represents an OpenGL Vertex Array Object.
 *
 * The VAO class encapsulates an OpenGL Vertex Array Object, providing methods to create, bind, unbind, and remove the VAO.
 */
class VAO
{
private:
  GLuint id;

public:
  /**
   * @brief Constructs an empty VAO object.
   */
  VAO();

  /**
   * @brief Binds the VAO to the current OpenGL context.
   */
  void linkVBO(VBO &VBO, GLuint layout);

  /**
   * @brief Binds the VAO to the current OpenGL context.
   */
  void bind();
  
  /**
   * @brief Unbinds the VAO from the current OpenGL context.
   */
  void unbind();
  
  /**
   * @brief Removes the VAO from the current OpenGL context.
   */
  void remove();
};

#endif // VAO_H