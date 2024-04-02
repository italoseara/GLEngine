#include "shaders.h"

string read_file(string filename)
{
  ifstream in(filename, ios::binary);
  if (!in)
  {
    cerr << "Error opening file: " << filename << endl;
    exit(EXIT_FAILURE);
  }

  string contents;
  in.seekg(0, ios::end);
  contents.resize(in.tellg());
  in.seekg(0, ios::beg);
  in.read(&contents[0], contents.size());
  in.close();

  return contents;
}

Shader::Shader(string vertex_path, string fragment_path)
{
  string vertex_code = read_file(vertex_path);
  string fragment_code = read_file(fragment_path);

  const char *vertex_source = vertex_code.c_str();
  const char *fragment_source = fragment_code.c_str();

  // Compile vertex shader
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_source, NULL);
  glCompileShader(vertex_shader);

  // Check for shader compilation errors
  check(vertex_shader, "VERTEX");

  // Compile fragment shader
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_source, NULL);
  glCompileShader(fragment_shader);

  // Check for shader compilation errors
  check(fragment_shader, "FRAGMENT");

  // Link shaders
  id = glCreateProgram();
  glAttachShader(id, vertex_shader);
  glAttachShader(id, fragment_shader);
  glLinkProgram(id);

  // Check for linking errors
  check(id, "PROGRAM");

  // Delete shaders
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void Shader::activate()
{
  glUseProgram(id);
}

void Shader::remove()
{
  glDeleteProgram(id);
}

GLuint Shader::get_id()
{
  return id;
}

void Shader::check(unsigned int shader, string type)
{
  GLint success;
  char info_log[1024];
  if (type != "PROGRAM")
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(shader, 1024, NULL, info_log);
      cerr << "Shader compilation failed (" << type << "): " << info_log << endl;
    }
  }
  else
  {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(shader, 1024, NULL, info_log);
      cerr << "Shader linking failed (" << type << "): " << info_log << endl;
    }
  }
}