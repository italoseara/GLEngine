/*
 * engine.h
 * Created on: Mar 26, 2024
 * Author: Italo Santana Seara
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <chrono>
#include <string>
#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

using namespace std;

/**
 * @brief The vertex shader source code.
 *
 * This string contains the source code for the vertex shader. It specifies the version of the shader,
 * the layout of the input attribute, and the transformation of the vertex position.
 */
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

/**
 * @brief The fragment shader source code.
 *
 * This variable stores the source code for the fragment shader. It is a string
 * containing GLSL code that sets the output color to white.
 */
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(PLACEHOLDER_Rf, PLACEHOLDER_Gf, PLACEHOLDER_Bf, PLACEHOLDER_Af);\n"
                                   "}\n\0";

/**
 * @class Engine
 * @brief The Engine class represents the main engine for the application.
 *
 * The Engine class is responsible for initializing the GLFW library, creating and managing the window,
 * handling the main loop, and providing utility functions for measuring frames per second (FPS) and delta time.
 */
class Engine
{
private:
  GLFWwindow *window;

  bool debug = false;

  string title;
  int width, height;

  int fps = 0;
  int frames = 0;
  int64_t lastSecond = 0;
  int64_t lastFrame = 0;

  GLuint shaderProgram;

  /**
   * Logs the given message.
   *
   * @param message The message to be logged.
   */
  void log(string message)
  {
    if (debug)
    {
      cout << "[ENGINE] " << message << "\n";
    }
  }

public:
  /**
   * @brief Constructs an Engine object with the specified title, width, and height.
   *
   * @param title The title of the engine window.
   * @param width The width of the engine window.
   * @param height The height of the engine window.
   */
  Engine(string title, int width, int height) : title(title), width(width), height(height)
  {
    if (!glfwInit())
    {
      cerr << "Failed to initialize GLFW\n";
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Destructor for the Engine class.
   */
  ~Engine()
  {
    glfwTerminate();
    glDeleteProgram(shaderProgram);
  }

  /**
   * Sets the debug mode.
   *
   * @param debug The debug mode.
   */
  void setDebug(bool debug)
  {
    this->debug = debug;
  }

  /**
   * Gets the debug mode.
   *
   * @return The debug mode.
   */
  bool getDebug()
  {
    return debug;
  }

  /**
   * Gets the frames per second (FPS).
   *
   * @return The frames per second (FPS).
   */
  int getFps()
  {
    return fps;
  }

  /**
   * Calculates the time elapsed since the last frame in seconds.
   *
   * @return The time elapsed since the last frame in seconds.
   */
  double getDeltaTime()
  {
    return (getTimestamp() - lastFrame) / 1000.0;
  }

  /**
   * Returns the current timestamp in milliseconds.
   *
   * @return The current timestamp in milliseconds.
   */
  int64_t getTimestamp()
  {
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
  }

  /**
   * @brief Get the width of the engine.
   * 
   * @return The width of the engine.
   */
  int getWidth()
  {
    return width;
  }

  /**
   * @brief Get the height of the object.
   * 
   * @return The height of the object.
   */
  int getHeight()
  {
    return height;
  }

  /**
   * Returns the shader program.
   *
   * @return The shader program.
   */
  GLuint getShaderProgram()
  {
    return shaderProgram;
  }

  /**
   * @brief Called once before the engine starts running.
   *
   * This function is called to initialize the engine before it starts running.
   * Can be called again to reset the state of the engine.
   * It can be overridden by derived classes to perform any necessary initialization tasks.
   */
  virtual void init() {}

  /**
   * @brief Called every frame to update the engine's state.
   *
   * This function is called to update the engine's state.
   * It should be overridden by derived classes to implement
   * the specific update logic.
   */
  virtual void update() {}

  /**
   * @brief Called every frame to render the engine's state.
   *
   * This function should be overridden by derived classes to implement the rendering logic.
   */
  virtual void render() {}

  /**
   * @brief Called once after the engine has finished running.
   *
   * This function is called to cleanup the engine after it has finished running.
   * It can be overridden by derived classes to perform any necessary cleanup tasks.
   */
  virtual void cleanup() {}

  /**
   * Runs the engine.
   */
  void run()
  {
    // Log the OpenGL version
    log("OpenGL Version: " + string((char *)glfwGetVersionString()));

    // Create window and thows an error if it fails
    log("Creating window...");
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window)
    {
      cerr << "Failed to create window\n";
      glfwTerminate();
      exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, width, height);

    setupShadersProgram();

    // Starts the running loop
    log("Running...");

    init();
    while (!glfwWindowShouldClose(window))
    {
      // Update and Render the scene
      update();
      render();

      // FPS Counter
      frames++;
      if (getTimestamp() - lastSecond >= 1000)
      {
        fps = frames;
        frames = 0;
        lastSecond = getTimestamp();
      }

      // DeltaTime
      lastFrame = getTimestamp();

      // Handle events and swap buffers
      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    // After the program is closed
    log("Destroying window...");

    cleanup();
    glfwDestroyWindow(window);
  }

  /**
   * Sets up the shaders program.
   * This function creates and compiles the vertex and fragment shaders,
   * attaches the vertex shader to the shader program, and links the shader program.
   */
  void setupShadersProgram()
  {
    // Create and compile the vertex and fragment shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create the shader program
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
  }

  /**
   * Sets the fragment shader for the shader program.
   *
   * @param source The source code of the fragment shader.
   */
  void setFragmentShader(const char *source)
  {
    // Remove the old fragment shader
    glDeleteProgram(shaderProgram);
    setupShadersProgram();

    // Create and compile the new fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &source, NULL);
    glCompileShader(fragmentShader);

    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(fragmentShader);
  }

  /**
   * Sets the color values for the fragment shader.
   *
   * @param r The red component of the color (0.0 - 1.0).
   * @param g The green component of the color (0.0 - 1.0).
   * @param b The blue component of the color (0.0 - 1.0).
   * @param a The alpha component of the color (0.0 - 1.0).
   */
  void setColor(float r, float g, float b, float a)
  {
    // Replace the placeholder values in the fragment shader
    string fragmentShader = fragmentShaderSource;
    fragmentShader.replace(fragmentShader.find("PLACEHOLDER_R"), 13, to_string(r));
    fragmentShader.replace(fragmentShader.find("PLACEHOLDER_G"), 13, to_string(g));
    fragmentShader.replace(fragmentShader.find("PLACEHOLDER_B"), 13, to_string(b));
    fragmentShader.replace(fragmentShader.find("PLACEHOLDER_A"), 13, to_string(a));

    setFragmentShader(fragmentShader.c_str());
  }

  /**
   * @brief Sets the color values for the fragment shader.
   *
   * @param r The red component of the color (0.0 - 1.0).
   * @param g The green component of the color (0.0 - 1.0).
   * @param b The blue component of the color (0.0 - 1.0).
   */
  void setColor(float r, float g, float b)
  {
    setColor(r, g, b, 1.0f);
  }

  /**
   * @brief Sets the color values for the fragment shader.
   *
   * @param r The red component of the color (0 - 255).
   * @param g The green component of the color (0 - 255).
   * @param b The blue component of the color (0 - 255).
   * @param a The alpha component of the color (0 - 255).
   */
  void setColor(int r, int g, int b, int a)
  {
    setColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
  }

  /**
   * @brief Sets the color values for the fragment shader.
   *
   * @param r The red component of the color (0 - 255).
   * @param g The green component of the color (0 - 255).
   * @param b The blue component of the color (0 - 255).
   */
  void setColor(int r, int g, int b)
  {
    setColor(r, g, b, 255);
  }

  /**
   * @brief Sets the color values for the fragment shader.
   *
   * @param hex The color in hexadecimal format (e.g., 0xFF0000 for red).
   */
  void setColor(int hex)
  {
    setColor((hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF);
  }

  /**
   * Clears the color buffer with the specified color.
   *
   * @param r The red component of the color (between 0.0 and 1.0).
   * @param g The green component of the color (between 0.0 and 1.0).
   * @param b The blue component of the color (between 0.0 and 1.0).
   * @param a The alpha component of the color (between 0.0 and 1.0).
   */
  void clearColor(float r, float g, float b, float a)
  {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
  }
};

#endif // ENGINE_H