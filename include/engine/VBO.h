#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

class VBO
{
private:
  GLuint id;

public:
  VBO() {}
  VBO(GLfloat *vertices, GLsizeiptr size);
  void bind();
  void unbind();
  void remove();
};

#endif // VBO_H