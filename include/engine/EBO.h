#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

class EBO
{
private:
  GLuint id;

public:
  EBO() {}
  EBO(GLuint *indices, GLsizeiptr size);
  void bind();
  void unbind();
  void remove();
};

#endif // VBO_H