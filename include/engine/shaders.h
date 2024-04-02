#ifndef SHADERS_H
#define SHADERS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

string read_file(const char *filename);

/**
 * @class Shader
 * @brief Represents an OpenGL shader program.
 *
 * The Shader class encapsulates an OpenGL shader program, providing methods to compile, link, and use the shader program.
 */
class Shader
{
private:
  GLuint id;

public:
  Shader() {}

  /**
   * @brief Constructs a Shader object from the specified vertex and fragment shader files.
   *
   * This constructor loads the vertex and fragment shader source code from the specified files, 
   * compiles them, and links them into a shader program.
   *
   * @param folder_path The path to the folder containing the vertex and fragment shader files.
   * @param vertex_file The name of the vertex shader file.
   * @param fragment_file The name of the fragment shader file.
   */
  Shader(string folder_path, string vertex_file, string fragment_file);

  /**
   * @brief Activates the shader program for rendering.
   */
  void use();

  /**
   * @brief Removes the shader program from the current rendering state.
   */
  void remove();
};

#endif