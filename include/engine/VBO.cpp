#include "VBO.h"

VBO::VBO(GLfloat *vertices, GLsizeiptr size)
{
  glGenBuffers(1, &id);
  bind();
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::remove()
{
  glDeleteBuffers(1, &id);
}