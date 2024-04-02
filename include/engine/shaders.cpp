#include "shaders.h"

string read_file(const char *filename)
{
  ifstream in(filename, ios::binary);
  if (!in) {
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

Shader::Shader(string folder_path, string vertex_file, string fragment_file)
{
  string vertex_code = read_file((folder_path + "/" + vertex_file).c_str());
  string fragment_code = read_file((folder_path + "/" + fragment_file).c_str());

  const char *vertex_source = vertex_code.c_str();
  const char *fragment_source = fragment_code.c_str();

  // Compile vertex shader
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_source, NULL);
  glCompileShader(vertex_shader);

  // Check for shader compilation errors
  GLint success;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char info_log[512];
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
    cerr << "Vertex shader compilation failed: " << info_log << endl;
  }

  // Compile fragment shader
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_source, NULL);
  glCompileShader(fragment_shader);

  // Check for shader compilation errors
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char info_log[512];
    glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
    cerr << "Fragment shader compilation failed: " << info_log << endl;
  }

  // Link shaders
  id = glCreateProgram();
  glAttachShader(id, vertex_shader);
  glAttachShader(id, fragment_shader);
  glLinkProgram(id);

  // Check for linking errors
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success)
  {
    char info_log[512];
    glGetProgramInfoLog(id, 512, NULL, info_log);
    cerr << "Shader program linking failed: " << info_log << endl;
  }

  // Delete shaders
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void Shader::use()
{
  glUseProgram(id);
}

void Shader::remove()
{
  glDeleteProgram(id);
}