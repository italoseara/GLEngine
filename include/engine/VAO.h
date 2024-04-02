#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
private:
  GLuint id;

public:
  VAO();
  void linkVBO(VBO &VBO, GLuint layout);
  void bind();
  void unbind();
  void remove();
};

#endif // VAO_H